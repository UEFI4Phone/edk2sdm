# Samsung S8 EDK2 Port

[![GitHub stars](https://img.shields.io/github/stars/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/network)
[![GitHub issues](https://img.shields.io/github/issues/evsio0n/edk2sdm)](https://github.com/evsio0n/edk2sdm/issues)


Build status:

[![Build Status](https://dev.azure.com/1344729087/edk2sdm/_apis/build/status/Evsio0n.edk2sdm?branchName=master)](https://dev.azure.com/1344729087/edk2sdm/_build/latest?definitionId=2&branchName=master)

## How to build

Tested in :

System|Version
-|-
Ubuntu|18.04LTS
Ubuntu|16.04LTS

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
[Video Link](https://www.youtube.com/watch?v=k6zNKBpKHwo)
<div align="center">
    <iframe width="620" height="315"
        src="https://www.youtube.com/watch?v=k6zNKBpKHwo">
    </iframe>
</div>
