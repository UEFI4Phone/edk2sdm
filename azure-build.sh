#!/bin/bash
set -e
sudo apt update
sudo apt install -y build-essential uuid-dev iasl git nasm gcc-aarch64-linux-gnu bc
curdir="$PWD"
cd "$curdir"
sudo chmod a+x * -R
export PACKAGES_PATH=$PWD/edk2:$PWD/edk2-platforms:$PWD/Sdm835
export WORKSPACE=$PWD/workspace
. ./edk2/edksetup.sh
make -C ./edk2/BaseTools
. ./edk2/edksetup.sh
GCC5_AARCH64_PREFIX=aarch64-linux-gnu- build -s -n 0 -a AARCH64 -t GCC5 -p SamsungS8Pkg/SamsungS8Pkg.dsc
gzip -9nkc < workspace/Build/SamsungS8Pkg/DEBUG_GCC5/FV/SAMSUNGS8PKG_UEFI.fd >uefi.img
cat uefi.img devicetree.dtb >> ./tools/split_img/boot.img-zImage
bash ./tools/repackimg.sh
