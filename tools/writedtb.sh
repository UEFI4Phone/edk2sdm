#!/bin/sh -e
outdir="tmp"
imagepath=$1
echo -n 'Enter path to your boot.img: '
read bootimgpath
python tools/unpackbootimg.py -i $bootimgpath -o $outdir
cat $(find $outdir -name *-zImage.fdt) >>"$imagepath"
rm -R $outdir
exit 0
