gzip -9nkc < workspace/Build/SamsungS8Pkg/DEBUG_GCC5/FV/SAMSUNGS8PKG_UEFI.fd >uefi.img
cat uefi.img devicetree.dtb >> ./tools/split_img/boot.img-zImage
bash ./tools/repackimg.sh

