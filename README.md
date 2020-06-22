# Samsung S8 EDK2 Port

[![GitHub stars](https://img.shields.io/github/stars/UEFI4Phone/edk2sdm)](https://github.com/UEFI4Phone/edk2sdm/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/UEFI4Phone/edk2sdm)](https://github.com/UEFI4Phone/edk2sdm/network)
[![GitHub issues](https://img.shields.io/github/issues/UEFI4Phone/edk2sdm)](https://github.com/UEFI4Phone/edk2sdm/issues)


Build status:

![CI Build Status](https://github.com/UEFI4Phone/edk2sdm/workflows/C/C++%20CI/badge.svg)

## How to build（Dirty）

Tested in :

System|Version|Status
-|-|-
Ubuntu|18.04LTS|✅
Ubuntu|16.04LTS|✅
Ubuntu|20.04LTS|✅
Debian|Buster|✅

Build with 

`bash ./build.sh` 

You'll get boot.img at 

`./tools/image-new.img`

MMU Works Fine now.
Currently can load Windows Boot.wim.
Thanks to @fxsheep @imbushuo 

## Flash instructions 

Flash a newest official rom with TWRP recovery, then download boot.img at release page flash it then you can get UEFI loader now.Or you can build your self with my script.

## Status
MMU Seems Fine. Need to implement some ACPI tables.

## Videos
[![Video Link](https://s1.ax1x.com/2020/04/24/JDojEt.png)](https://www.youtube.com/watch?v=k6zNKBpKHwo)

