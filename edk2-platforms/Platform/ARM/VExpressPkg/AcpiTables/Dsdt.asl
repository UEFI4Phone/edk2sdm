/*
* Copyright (c) 2013, Al Stone <al.stone@linaro.org>
* All rights reserved.
*
* SPDX-License-Identifier: BSD-2-Clause-Patent
*
*
* NB: This License is also known as the "BSD 2-Clause License".
*
*
* [DSDT] Description of the armv8 VE Model
*
*/

DefinitionBlock (
  "dsdt.aml",    // output filename
  "DSDT",      // table signature
  2,      // DSDT compliance revision
  "LINARO",    // OEM ID
  "RTSMVEV8",    // table ID
  0x00000004)    // OEM revision
{
  Scope (\_SB)
  {
    Method (_OSC, 4, NotSerialized)
    {
      /* Platform-Wide OSPM Capabilities */
      If(LEqual(Arg0,ToUUID("0811B06E-4A27-44F9-8D60-3CBBC22E7B48")))
      {
        /* APEI support unconditionally */
        Return (Arg3)
      } Else {
        CreateDWordField (Arg3, Zero, CDW1)
        /* Set invalid UUID error bit */
        Or (CDW1, 0x04, CDW1)
        Return (Arg3)
      }
    }

    //
    // Two Emulated aarch64 CPUs each with 4 cores
    //
    Device(CPU0) { // Cluster 0, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 0)
    }
    Device(CPU1) { // Cluster 0, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 1)
    }
    Device(CPU2) { // Cluster 0, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 2)
    }
    Device(CPU3) { // Cluster 0, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 3)
    }
    Device(CPU4) { // Cluster 1, Cpu 0
      Name(_HID, "ACPI0007")
      Name(_UID, 4)
    }
    Device(CPU5) { // Cluster 1, Cpu 1
      Name(_HID, "ACPI0007")
      Name(_UID, 5)
    }
    Device(CPU6) { // Cluster 1, Cpu 2
      Name(_HID, "ACPI0007")
      Name(_UID, 6)
    }
    Device(CPU7) { // Cluster 1, Cpu 3
      Name(_HID, "ACPI0007")
      Name(_UID, 7)
    }

    // SMC91X
    Device (NET0) {
      Name (_HID, "LNRO0003")
      Name (_UID, 0)

      Name (_CRS, ResourceTemplate () {
        Memory32Fixed (ReadWrite, 0x1a000000, 0x00010000)
        Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive, , , ) {0x2F}
      })
    }

    // SYSREG
    Device (SREG) {
      Name (_HID, "LNRO0009")
      Name (_UID, 0)

      Method (_CRS, 0x0, Serialized) {
        Name (RBUF, ResourceTemplate() {
          Memory32Fixed (ReadWrite, 0x1c010000, 0x1000)
        })
        Return (RBUF)
      }
    }

    // VIRTIO
    Device (VIRT) {
      Name (_HID, "LNRO0005")
      Name (_UID, 0)

      Name (_CRS, ResourceTemplate() {
        Memory32Fixed (ReadWrite, 0x1c130000, 0x1000)
        Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) {0x4A}
      })
    }

    // UART PL011
    Device(COM0) {
      Name(_HID, "ARMH0011")
      Name(_CID, "PL011")
      Name(_UID, Zero)

      Name(_CRS, ResourceTemplate() {
        Memory32Fixed(ReadWrite, 0x1c090000, 0x1000)
        Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 0x25 }
      })
    }
  }
}
