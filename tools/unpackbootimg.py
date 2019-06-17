#!/usr/bin/env python
# Copyright 2015, The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from __future__ import print_function
from sys import exit
from argparse import ArgumentParser, FileType
from os import rename, makedirs
from os.path import basename, exists
from struct import unpack, calcsize
import zlib
import subprocess

HAS_ELFTOOLS = True
try:
    from elftools.elf.elffile import ELFFile
    from elftools.elf.sections import SymbolTableSection
except:
    HAS_ELFTOOLS = False

def ROUNDDOWN(number, alignment):
    return ((number) & ~((alignment)-1))

class Bunch:
    def __init__(self, **kwds):
        self.__dict__.update(kwds)

def auto_unpack(fmt, f):
    size = calcsize(fmt)
    data = f.read(size)
    return unpack(fmt, data[0:size])

def get_magic_off(f):
    BOOT_MAGIC = 'ANDROID!'.encode()

    for i in range(513):
        f.seek(i)
        tmp = f.read(len(BOOT_MAGIC))
        if tmp == BOOT_MAGIC:
            #print('Android magic found at: %d' % i)
            return i

    return -1

def read_header(args, off):
    args.input.seek(off)
    fmt = '8s10I16s512s32s1024s'
    unpacked = auto_unpack(fmt, args.input)

    parsed = Bunch()
    parsed.type = 'android'
    parsed.headersz = calcsize(fmt)
    parsed.magic = unpacked[0]
    parsed.kernel_size = unpacked[1]
    parsed.kernel_addr = unpacked[2]
    parsed.ramdisk_size = unpacked[3]
    parsed.ramdisk_addr = unpacked[4]
    parsed.second_size = unpacked[5]
    parsed.second_addr = unpacked[6]
    parsed.tags_addr = unpacked[7]
    parsed.pagesize = unpacked[8]
    parsed.dt_size = unpacked[9]
    parsed.name = unpacked[11].partition(b'\0')[0].decode()
    parsed.cmdline = unpacked[12].partition(b'\0')[0].decode()
    parsed.id = unpacked[13]
    parsed.cmdline += unpacked[14].partition(b'\0')[0].decode()

    os_version = unpacked[10]>>11
    os_patch_level = unpacked[10]&0x7ff

    parsed.os_version = None
    if os_version != 0:
        a = (os_version>>14)&0x7f
        b = (os_version>>7)&0x7f
        c = os_version&0x7f
        parsed.os_version = '%d.%d.%d' % (a,b,c)

    parsed.os_patch_level = None
    if os_patch_level != 0:
        y = (os_patch_level>>4) + 2000
        m = os_patch_level&0xf
        parsed.os_patch_level = '%04d-%02d-%02d' % (y,m,0)

    return parsed

def parse_elf(stream):
    try:
        elffile = ELFFile(stream)
    except:
        #print('Android boot magic not found.')
        exit(1)

    parsed = Bunch()
    parsed.type = 'elf'
    parsed.kernel_size = 0
    parsed.kernel_addr = 0
    parsed.ramdisk_size = 0
    parsed.ramdisk_addr = 0
    parsed.second_size = 0
    parsed.second_addr = 0
    parsed.tags_addr = 0
    parsed.pagesize = 2048
    parsed.dt_size = 0
    parsed.name = ''
    parsed.cmdline = ''
    parsed.id = ''
    parsed.os_version = None
    parsed.os_patch_level = None

    for i in range(elffile['e_phnum']):
        stream.seek(elffile['e_phoff'] + i * elffile['e_phentsize'])
        phdr = elffile.structs.Elf_Phdr.parse_stream(stream)

        if i==0:
            parsed.kernel_file_offset = phdr['p_offset']
            parsed.kernel_size = phdr['p_filesz']
            parsed.kernel_addr = phdr['p_paddr']
        elif i==1:
            parsed.ramdisk_file_offset = phdr['p_offset']
            parsed.ramdisk_size = phdr['p_filesz']
            parsed.ramdisk_addr = phdr['p_paddr']
        elif i==2:
            parsed.dt_file_offset = phdr['p_offset']
            parsed.dt_size = phdr['p_filesz']
            parsed.tags_addr = phdr['p_paddr']

    for i in range(elffile['e_shnum']):
        stream.seek(elffile['e_shoff'] + i * elffile['e_shentsize'])
        shdr = elffile.structs.Elf_Shdr.parse_stream(stream)

        stream.seek(shdr['sh_offset'])
        parsed.cmdline = stream.read(shdr['sh_size'])[8:].partition(b'\0')[0].decode()

    return parsed

def write_str_to_file(filename, s):
    with open(filename, 'wb') as f:
        f.write(s.encode())

def parse_int(x):
    return int(x, 0)

def parse_cmdline():
    parser = ArgumentParser()
    parser.add_argument('-i', '--input', help='input file name', type=FileType('rb'),
                        required=True)
    parser.add_argument('-o', '--output', help='output directory', default='./')
    parser.add_argument('--pagesize', help='page size', type=parse_int,
                        choices=[2**i for i in range(11,18)], default=0)
    return parser.parse_args()

def seek_padding(f, size, pagesize):
    pagemask = pagesize - 1;
    if((size & pagemask) != 0):
        count = pagesize - (size & pagemask);
        f.seek(count, 1);

def write_input_to_file(args, filename, size):
    with open(filename, 'wb') as f_out:
        f_out.write(args.input.read(size))

    seek_padding(args.input, size, args.pagesize)

def fix_ramdisk_extension(filename):
    bytes = []
    with open(filename, 'rb') as f:
        data = f.read(2)
        if(len(data))!=2:
            return
        bytes = unpack('BB', data)

    if bytes[0]==0x02 and bytes[1]==0x21:
        rename(filename, filename+'.lz4')
    else:
        rename(filename, filename+'.gz')

def is_gzip_package(filename):
    bytes = []
    with open(filename, 'rb') as f:
        data = f.read(3)
        if(len(data))!=3:
            return False
        bytes = unpack('BBB', data)

    return bytes[0]==0x1f and bytes[1]==0x8b and bytes[2]==0x08

def is_arm64(filename):
    data = None
    with open(filename, 'rb') as f:
        fmt = '2I6Q2I'
        size = calcsize(fmt)
        buf = f.read(size)
        if(len(buf))!=size:
            return False
        data = unpack(fmt, buf)

    return data[8]==0x644D5241

def is_lz4(filename):
    data = None
    with open(filename, 'rb') as f:
        fmt = '>I'
        size = calcsize(fmt)
        buf = f.read(size)
        if(len(buf))!=size:
            return False
        data = unpack(fmt, buf)

    return data[0]==0x04224D18 or data[0]==0x02214C18

def write_data(args, header, off):
    file_prefix = args.output
    if file_prefix and file_prefix[-1]!='/':
        file_prefix += '/'
    file_prefix += basename(args.input.name) + '-'

    if not exists(args.output):
        makedirs(args.output)

    write_str_to_file(file_prefix+'cmdline', header.cmdline)
    write_str_to_file(file_prefix+'base', '%08x' % header.base)
    write_str_to_file(file_prefix+'kernel_offset', '%08x' % header.kernel_offset)
    write_str_to_file(file_prefix+'ramdisk_offset', '%08x' % header.ramdisk_offset)
    write_str_to_file(file_prefix+'second_offset', '%08x' % header.second_offset)
    write_str_to_file(file_prefix+'tags_offset', '%08x' % header.tags_offset)
    write_str_to_file(file_prefix+'pagesize', '%d' % header.pagesize)
    write_str_to_file(file_prefix+'name', header.name)
    if header.os_version:
        write_str_to_file(file_prefix+'os_version', header.os_version)
    if header.os_patch_level:
        write_str_to_file(file_prefix+'os_patch_level', header.os_patch_level)

    if header.type=='android':
        seek_padding(args.input, header.headersz, args.pagesize)
        write_input_to_file(args, file_prefix+'zImage', header.kernel_size)
        write_input_to_file(args, file_prefix+'ramdisk', header.ramdisk_size)
        write_input_to_file(args, file_prefix+'second', header.second_size)
        write_input_to_file(args, file_prefix+'dt', header.dt_size)
    elif header.type=='elf':
        args.input.seek(header.kernel_file_offset)
        write_input_to_file(args, file_prefix+'zImage', header.kernel_size)

        args.input.seek(header.ramdisk_file_offset)
        write_input_to_file(args, file_prefix+'ramdisk', header.ramdisk_size)

        args.input.seek(header.dt_file_offset)
        write_input_to_file(args, file_prefix+'dt', header.dt_size)

    fix_ramdisk_extension(file_prefix+'ramdisk')

    if header.kernel_size >= 2:
        if is_gzip_package(file_prefix+'zImage'):
            with open(file_prefix+'zImage', 'rb') as f_in:
                # seek past gzip header
                f_in.seek(10)

                # write uncompressed zImage
                with open(file_prefix+'zImage.gunzip', 'wb') as f_out:
                    decomp = zlib.decompressobj(-15)
                    f_out.write(decomp.decompress(f_in.read()))

                # write fdt
                if len(decomp.unused_data)>8:
                    with open(file_prefix+'zImage.fdt', 'wb') as f_out:
                        f_out.write(decomp.unused_data[8:])

        elif not is_arm64(file_prefix+'zImage'):
            with open(file_prefix+'zImage', 'rb') as f_in:
                # get kernel size
                f_in.seek(0x28)
                unpacked = auto_unpack('2I', f_in)
                zimage_start = unpacked[0]
                zimage_end = unpacked[1]
                zimage_size = zimage_end - zimage_start;

                if zimage_size<header.kernel_size:
                    # write zImage
                    f_in.seek(0)
                    with open(file_prefix+'zImage.real', 'wb') as f_out:
                        f_out.write(f_in.read(zimage_size))

                    trailername = 'zImage.trailer'
                    trailerdata = f_in.read()
                    if len(trailerdata)>4 and trailerdata[0:4]=='\xd0\x0d\xfe\xed':
                        trailername = 'zImage.fdt'

                    # write fdt
                    with open(file_prefix+trailername, 'wb') as f_out:
                        f_out.write(trailerdata)

    if header.dt_size >= 4:
        if is_lz4(file_prefix+'dt'):
            p = subprocess.Popen(['lz4', '-d', '-f', file_prefix+'dt', file_prefix+'dt.unlz4'], stdout=subprocess.PIPE)
            data = p.communicate()[0]
            if p.returncode != 0:
                pr_fatal('can\'t extract LZ4 dt.img')

def main():
    args = parse_cmdline()
    off = get_magic_off(args.input)
    if off >= 0:
        header = read_header(args, off)
    else:
        off = 0
        args.input.seek(off)
        header = parse_elf(args.input)

    # find common base of all loading addresses
    header.base = min(header.kernel_addr, header.ramdisk_addr, header.second_addr, header.tags_addr)
    header.base = ROUNDDOWN(header.base, header.pagesize)
    if (header.base&0xffff) == 0x8000:
        header.base -= 0x8000

    # calculate offsets relative to base
    header.kernel_offset = header.kernel_addr - header.base
    header.ramdisk_offset = header.ramdisk_addr - header.base
    header.second_offset = header.second_addr - header.base
    header.tags_offset = header.tags_addr - header.base

    #print('BOARD_KERNEL_CMDLINE %s' % header.cmdline)
    #print('BOARD_KERNEL_BASE %08x' % header.kernel_offset)
    #print('BOARD_RAMDISK_OFFSET %08x' % header.ramdisk_offset)
    #print('BOARD_SECOND_OFFSET %08x' % header.second_offset)
    #print('BOARD_TAGS_OFFSET %08x' % header.tags_offset)
    #print('BOARD_PAGE_SIZE %d' % header.pagesize)
    #print('BOARD_SECOND_SIZE %d' % header.second_size)
    #print('BOARD_DT_SIZE %d' % header.dt_size)

    if args.pagesize == 0:
        args.pagesize = header.pagesize

    write_data(args, header, off)

if __name__ == '__main__':
    main()
