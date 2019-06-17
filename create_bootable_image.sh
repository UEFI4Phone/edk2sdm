#!/bin/sh -e
echo "Choose the platform: "
echo "1. Snapdragon 835"
echo "2. Snapdragon 845"
echo -n "Enter your choice: "
read platform_num
case "$platform_num" in
    1)
      platform="Sdm835"
      ;;
    2)
      platform="Sdm845"
      ;;
    *)
      echo "Invalid platform!"
      exit 2
      ;;
esac
uid=$(id -u)
if [ "$uid" -eq "0" ]; then
    echo "Installing dependencies"
    apt-get install build-essential uuid-dev iasl git nasm python3-distutils gcc-aarch64-linux-gnu python gcc make -y
else
    echo 'You need to install some dependencies to continue building of UEFI, but it needs using command "sudo", and in many cases it will request your password. Installation of dependencies will be started and, if needed, you have to enter your password.'
    sudo apt-get install build-essential uuid-dev iasl git nasm python3-distutils gcc-aarch64-linux-gnu python gcc make -y
fi
rm -f zImage fdt.img $platform/uefi.img
tools/writedtb.sh fdt.img
rm -Rf edk2/Conf
mkdir -m 755 edk2/Conf
echo "Building UEFI"
cd $platform
if [ ! -d workspace ]; then
    mkdir -m 755 workspace
fi
rm -Rf workspace/Build
unset EDK_TOOLS_PATH GCC5_AARCH64_PREFIX WORKSPACE CONF_PATH
./firstrun.sh
./build.sh
cd ..
cat $platform/uefi.img fdt.img > zImage
rm $platform/uefi.img fdt.img
echo 'Done! File "zImage" is a bootable UEFI image, which can be booted by command "fastboot boot zImage" when bootloader is unlocked'
exit 0
