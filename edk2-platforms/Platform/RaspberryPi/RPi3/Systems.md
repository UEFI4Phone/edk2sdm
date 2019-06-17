# Tested Operating Systems

## Ubuntu

[Ubuntu 18.04 LTS](http://releases.ubuntu.com/18.04/) has been tested and confirmed to work,
on a Raspberry 3 Model B, including the installation process. Note however that network
installation and networking may not work on the Model B+, due to the `lan78xx` Linux driver
still requiring some support.

Below are the steps you can follow to install Ubuntu LTS onto SD/USB:
* Download the latest Ubuntu LTS ARM64 [`mini.iso`](http://ports.ubuntu.com/ubuntu-ports/dists/bionic/main/installer-arm64/current/images/netboot/mini.iso).
* Partition the media as MBR and create a ~200 MB FAT32 partition on it with MBR type `0x0c`.
  Note: Do not be tempted to use GPT partition scheme or `0xef` (EFI System Partition) for the
  type, as none of these are supported by the Raspberry Pi's internal boot rom.
* Extract the full content of the ISO onto the partition you created.
* Also extract the GRUB EFI bootloader `bootaa64.efi` from `/boot/grub/efi.img` to `/boot/grub/`.
  Note: Do not be tempted to copy this file to another directory (such as `/efi/boot/`) as GRUB looks for its
  modules and configuration data in the same directory as the EFI loader and also, the installation
  process will create a `bootaa64.efi` into `/efi/boot/`.
* If needed, copy the UEFI firmware files (`RPI_EFI.fd`, `bootcode.bin`, `fixup.dat` and `start.elf`)
  onto the FAT partition.
* Boot the pi and let it go into the UEFI shell.
* Navigate to `fs0:` then `/boot/grub/` and launch the GRUB efi loader.
* Follow the Ubuntu installation process.

Note: Because Ubuntu operates in quiet mode by default (no boot messages), you may think the system is frozen
on first reboot after installation. However, if you wait long enough you **will** get to a login prompt.

Once Linux is running, if desired, you can disable quiet boot, as well as force the display
of the GRUB selector, by editing `/etc/default/grub` and changing:
* `GRUB_TIMEOUT_STYLE=hidden` &rarr; `GRUB_TIMEOUT_STYLE=menu`
* `GRUB_CMDLINE_LINUX_DEFAULT="splash quiet"` &rarr; `GRUB_CMDLINE_LINUX_DEFAULT=""`

Then, to have your changes applied run `update-grub` and reboot.

## Other Linux distributions

* Debian ARM64 does not currently work, most likely due to missing required module support
  in its kernel. However its installation process works, so it may be possible to get it
  running with a custom kernel.

* OpenSUSE Leap 42.3 has been reported to work on Raspberry 3 Model B.

* Other ARM64 Linux releases, that support UEFI boot and have the required hardware support
  for Pi hardware are expected to run, though their installation process might require some
  cajoling.

## Windows

Windows 10 1809 for ARM64 (build 17763) has been tested and confirmed to work (after replacing
`C:\Windows\System32\Drivers\WppRecorder.sys` with an older version, since the one from 1809
appears to be buggy across all archs, and results in a similar BSOD when trying to run Windows
To Go on x64 with native drivers for instance).

Windows 10 1803 for ARM64 and earlier do not work due to the presence of a hardware ASSERT check
in the Windows kernel, that was removed in later versions.

You probably want to look at https://www.worproject.ml/ as well as the
[Windows thread in the original RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg/issues/12)
for installation details.

## Other platforms

Details you may need to run other platforms, including FreeBSD, is provided in the
[Readme from the original RaspberryPiPkg](https://github.com/andreiw/RaspberryPiPkg).
