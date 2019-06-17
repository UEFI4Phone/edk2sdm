Raspberry Pi Platform
=====================

# Summary

This is a port of 64-bit Tiano Core UEFI firmware for the Raspberry Pi 3/3B+ platforms,
based on [Ard Bisheuvel's 64-bit](http://www.workofard.com/2017/02/uefi-on-the-pi/)
and [Microsoft's 32-bit](https://github.com/ms-iot/RPi-UEFI/tree/ms-iot/Pi3BoardPkg)
implementations, as maintained by [Andrei Warkentin](https://github.com/andreiw/RaspberryPiPkg).

This is meant as a generally useful 64-bit ATF + UEFI implementation for the Raspberry
Pi 3/3B+ which should be good enough for most kind of UEFI development, as well as for
running consummer Operating Systems in such as Linux or Windows.

Raspberry Pi is a trademark of the [Raspberry Pi Foundation](http://www.raspberrypi.org).

# Status

This firmware, that has been validated to compile against the current
[edk2](https://github.com/tianocore/edk2)/[edk2-platforms](https://github.com/tianocore/edk2-platforms),
should be able to boot Linux (SUSE, Ubuntu), NetBSD, FreeBSD as well as Windows 10 ARM64
(full GUI version).

It also provides support for ATF ([Arm Trusted Platform](https://github.com/ARM-software/arm-trusted-firmware)).

HDMI and the mini-UART serial port can be used for output devices, with mirrored output.
USB keyboards and the mini-UART serial port can be used as input.

On a freshly built firmware, the default is to boot the UEFI shell.
To change the default boot order (for instance to boot uSD media by default) you
will need to edit the preferences in _Boot Maintenance Manager_.

For additional information about the tested systems and how to set them up,
please see [Systems.md](./Systems.md).

# Building

Build instructions from the top level edk2-platforms Readme.md apply.

# Booting the firmware

1. Format a uSD card as FAT32
2. Copy the generated `RPI_EFI.fd` firmware onto the partition
3. Download and copy the following files from https://github.com/raspberrypi/firmware/tree/master/boot
  - `bootcode.bin`
  - `fixup.dat`
  - `start.elf`
4. Create a `config.txt` with the following content:
  ```
  arm_control=0x200
  enable_uart=1
  armstub=RPI_EFI.fd
  disable_commandline_tags=1
  ```
5. Insert the uSD card and power up the Pi.

Note that if you have a model 3+ or a model 3 where you enabled USB boot through OTP
(see [here](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bootmodes/msd.md))
you may also be able to boot from a FAT32 USB driver rather than uSD.

# Notes

## ARM Trusted Firmware (ATF)

The ATF binaries being used were compiled from the latest ATF source.
No aleration to the official source have been applied.

For more details on the ATF compilation, see the [Readme](./TrustedFirmware/Readme.md)
in the `TrustedFirmware/` directory.

## Custom Device Tree

The default Device Tree included in the firmware is the one for a Raspberry Pi 3 Model B (not B+).
If you want to use a different Device Tree, to boot a Pi 3 Model B+ for instance (for which a
DTB is also provided under `DeviceTree/`), you should copy the relevant `.dtb` into the root of
the SD or USB, and then edit your `config.txt` so that it looks like:

```
(...)
disable_commandline_tags=2
device_tree_address=0x10000
device_tree_end=0x20000
device_tree=bcm2710-rpi-3-b-plus.dtb
```

Note: the address range **must** be `[0x10000:0x20000]`.
`dtoverlay` and `dtparam` parameters are also supported **when** providing a Device Tree`.

## Custom `bootargs`

This firmware will honor the command line passed by the GPU via `cmdline.txt`.

Note, that the ultimate contents of `/chosen/bootargs` are a combination of several pieces:
- Original `/chosen/bootargs` if using the internal DTB. Seems to be completely discarded by GPU when booting with a custom device tree.
- GPU-passed hardware configuration. This one is always present.
- Additional boot options passed via `cmdline.txt`.

# Limitations

## HDMI

The UEFI HDMI video support relies on the VC (that's the GPU)
firmware to correctly detect and configure the attached screen.
Some screens are slow, and this detection may not occur fast
enough. Finally, you may wish to be able to boot your Pi
headless, yet be able to attach a display to it later for
debugging.

To accommodate these issues, the following extra lines
are recommended for your `config.txt`:
- `hdmi_force_hotplug=1` to allow plugging in video after system is booted.
- `hdmi_group=1` and `hdmi_mode=4` to force a specific mode, both to accommodate
   late-plugged screens or buggy/slow screens. See [official documentation](https://www.raspberrypi.org/documentation/configuration/config-txt/video.md)
   to make sense of these parameters (example above sets up 720p 60Hz).

## NVRAM

The Raspberry Pi has no NVRAM.

NVRAM is emulated, with the non-volatile store backed by the UEFI image itself. This means
that any changes made in UEFI proper are persisted, but changes made from a High Level
Operating System (HLOS) aren't.

## RTC

The Rasberry Pi has no RTC.

An `RtcEpochSeconds` NVRAM variable is used to store the boot time.
This should allow you to set whatever date/time you want using the Shell date and
time commands. While in UEFI or HLOS, the time will tick forward.
`RtcEpochSeconds` is not updated on reboots.

## uSD

UEFI supports both the Arasan SDHCI and the Broadcom SDHost controllers to access the uSD slot.
You can use either. The other controller gets routed to the SDIO card. The choice made will
impact ACPI OSes booted (e.g. Windows 10). Arasan, being an SDIO controller, is usually used
with the WiFi adapter where available. SDHost cannot be used with SDIO. In UEFI setup screen:
- go to `Device Manager`
- go to `Raspberry Pi Configuration`
- go to `Chipset`
- configure `Boot uSD Routing`

Known issues:
- Arasan HS/4bit support is missing.
- No 8 bit mode support for (e)MMC (irrelevant for the Pi 3).
- Hacky (e)MMC support (no HS).
- No card removal/replacement detection, tons of timeouts and slow down during boot without an uSD card present.

## USB

- USB1 BBB mass storage devices untested (USB2 and USB3 devices are fine).
- USB1 CBI mass storage devices don't work (e.g. HP FD-05PUB floppy).

## ACPI

Both Arasan and SDHost SD controllers are exposed.

Note that the ACPI tables were derived or copied from the MS-IoT one. This means that they
are not truly ACPI compliant, especially when it comes to their descriptors, and therefore
not suitable for Linux environments. If you want to use a Linux HLOS, you are encouraged to
install a kernel that relies on Device Tree rather than ACPI.

## Missing Functionality

- Network booting via onboard NIC.
- Ability to switch UART use to PL011.
