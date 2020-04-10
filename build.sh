#!/bin/bash
set -e
clear
echo "[Evsio0n]		Making EFI Booting by Evsio0n"
echo "[Evsio0n]		Now tested  in  18.04  Ubuntu"
echo "[Evsio0n]		Build starting..............."
sleep 2
echo "[Evsio0n]		Cleaning First..............."
bash ./clean.sh
echo "[Evsio0n]		Getting Depandenciences......"
sudo apt update
sudo apt install -y build-essential uuid-dev iasl git nasm gcc-aarch64-linux-gnu bc python3-pip python3-distutils
curdir="$PWD"
cd "$curdir"
#mkdir $PWD/workspace
export GCC5_AARCH64_PREFIX=aarch64-linux-gnu-
export PACKAGES_PATH=$PWD/edk2:$PWD/edk2-platforms:$PWD/Sdm835
export WORKSPACE=$PWD/workspace
. ./edk2/edksetup.sh > /dev/null
make -C ./edk2/BaseTools > /dev/null
clear
echo "[Evsio0n]		Now make FD Images..."
sleep 1
./tools/makefd.sh > /dev/null 
#GCC5_AARCH64_PREFIX=aarch64-linux-gnu- build -s -n 0 -a AARCH64 -t GCC5 -p XiaomiMI6Pkg/XiaomiMI6Pkg.dsc
echo "[Evsio0n]		Done!.............."
sleep 2
echo "[Evsio0n]		Now make zImages..."
./tools/makebootimg.sh > /dev/null
#gzip -9nkc < workspace/Build/XiaomiMI6Pkg/DEBUG_GCC5/FV/XIAOMIMI6PKG_UEFI.fd >uefi.img
#cat uefi.img devicetree.dtb >> ./tools/split_img/boot.img-zImage
#bash ./tools/repackimg.sh
echo "[Evsio0n]		Build done..........."
sudo rm -rf $PWD/workspace/*
echo "[Evsio0n]		Make Boot.img done..."
echo "[Evsio0n]		You can see it at ./tools/images-new.img"
echo "[Evsio0n]		./clean.sh can clean build boot.img"
echo "[Evsio0n]		Seeing at https://github.com/evsio0n/edk2sdm"
