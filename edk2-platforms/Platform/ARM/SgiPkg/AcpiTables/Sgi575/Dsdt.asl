/** @file
*  Differentiated System Description Table Fields (DSDT)
*
*  Copyright (c) 2018, ARM Ltd. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include "SgiPlatform.h"
#include "SgiAcpiHeader.h"

DefinitionBlock("DsdtTable.aml", "DSDT", 1, "ARMLTD", "ARMSGI", EFI_ACPI_ARM_OEM_REVISION) {
  Scope(_SB) {

    Device(CP00) { // A75-0: Cluster 0, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 0)
      Name(_STA, 0xF)
    }

    Device(CP01) { // A75-0: Cluster 0, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 1)
      Name(_STA, 0xF)
    }

    Device(CP02) { // A75-0: Cluster 0, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 2)
      Name(_STA, 0xF)
    }

    Device(CP03) { // A75-0: Cluster 0, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 3)
      Name(_STA, 0xF)
    }

    Device(CP04) { // A75-0: Cluster 1, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 4)
      Name(_STA, 0xF)
    }

    Device(CP05) { // A75-0: Cluster 1, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 5)
      Name(_STA, 0xF)
    }

    Device(CP06) { // A75-0: Cluster 1, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 6)
      Name(_STA, 0xF)
    }

    Device(CP07) { // A75-0: Cluster 1, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 7)
      Name(_STA, 0xF)
    }

    // UART PL011
    Device(COM0) {
      Name(_HID, "ARMH0011")
      Name(_CID, "ARMH0011")
      Name(_UID, Zero)
      Name(_STA, 0xF)
      Name(_CRS, ResourceTemplate() {
        Memory32Fixed(ReadWrite, 0x7FF80000, 0x1000)
        Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 147 }
      })
    }

    // SMSC 91C111
    Device(ETH0) {
      Name(_HID, "LNRO0003")
      Name(_UID, Zero)
      Name(_STA, 0xF)
      Name(_CRS, ResourceTemplate() {
            Memory32Fixed(ReadWrite, 0x18000000, 0x1000)
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 111 }
      })
      Name(_DSD, Package() {
                 ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
                     Package() {
                     Package(2) {"reg-io-width", 4 },
                    }
      })
    }
  } // Scope(_SB)

  // VIRTIO DISK
  Device (VR00) {
    Name (_HID, "LNRO0005")
    Name (_UID, 0)
    Name (_CCA, 1)    // mark the device coherent

    Name (_CRS, ResourceTemplate() {
      Memory32Fixed (
        ReadWrite,
        FixedPcdGet32 (PcdVirtioBlkBaseAddress),
        FixedPcdGet32 (PcdVirtioBlkSize)
      )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {
        FixedPcdGet32 (PcdVirtioBlkInterrupt)
      }
    })
  }

  // VIRTIO NET
  Device (VR01) {
    Name (_HID, "LNRO0005")
    Name (_UID, 1)
    Name (_CCA, 1)    // mark the device coherent

    Name (_CRS, ResourceTemplate() {
      Memory32Fixed (
        ReadWrite,
        FixedPcdGet32 (PcdVirtioNetBaseAddress),
        FixedPcdGet32 (PcdVirtioNetSize)
      )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {
        FixedPcdGet32 (PcdVirtioNetInterrupt)
      }
    })
  }
}
