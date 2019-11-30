# Samsung S8 EDK2 Port

[![GitHub stars](https://img.shields.io/github/stars/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/network)
[![GitHub issues](https://img.shields.io/github/issues/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/issues)


Build status:

[![Build Status](https://dev.azure.com/1344729087/edk2sdm/_apis/build/status/Evsio0n.edk2sdm?branchName=master)](https://dev.azure.com/1344729087/edk2sdm/_build/latest?definitionId=2&branchName=master)

## How to build

Env: Ubuntu 18.04
Build with 

`bash ./build.sh` 

You'll get boot.img at 

`./tools/image-new.img`

## Screenshots
[![1](https://i.loli.net/2019/11/22/pnwQi7y3JFUHBuL.jpg)](https://i.loli.net/2019/11/22/pnwQi7y3JFUHBuL.jpg)
[![2](https://i.loli.net/2019/11/22/LsuYZFVDx1Cf83b.jpg)](https://i.loli.net/2019/11/22/LsuYZFVDx1Cf83b.jpg)
[![3](https://i.loli.net/2019/11/22/2h4zTZyNIqGv9Dx.jpg)](https://i.loli.net/2019/11/22/2h4zTZyNIqGv9Dx.jpg)
Screen is Up.
Most of things seems fine now!

## Flash instructions 

Flash a newest official rom with TWRP recovery, then download boot.img at release page flash it then you can get UEFI loader now.  

## Status
I'm building recovery with Mass storage gadget so that some work can be done for Windows ARM64 : )
