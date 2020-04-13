echo "[Evsio0n]		Cleaning Boot File"
sleep 1
sudo rm -rf $PWD/workspace/*
echo "[Evsio0n]		Cl WorkSpace"
rm tools/ramdisk-new.cpio.gz
echo "[Evsio0n]		Cl ramdisk"
rm tools/split_img/boot.img-zImage
echo "[Evsio0n]		Cl zImage"
rm tools/image-new.img
echo "[Evsio0n]		Cl image-new.img"
rm uefi.img
echo "[Evsio0n]		Cl UEFI.img"
echo "[Evsio0n]		Sucess!"
