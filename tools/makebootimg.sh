gzip -9nkc < workspace/Build/XiaomiMI6Pkg/DEBUG_GCC5/FV/XIAOMIMI6PKG_UEFI.fd >uefi.img
cat uefi.img devicetree.dtb >> ./tools/split_img/boot.img-zImage
bash ./tools/repackimg.sh

