/** @file
*
*  Copyright (c) 2018, ARM Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>

#include <SgiPlatform.h>

// Total number of descriptors, including the final "end-of-table" descriptor.
#define MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS  13

/**
  Returns the Virtual Memory Map of the platform.

  This Virtual Memory Map is used by MemoryInitPei Module to initialize the MMU
  on your platform.

  @param[out] VirtualMemoryMap Array of ARM_MEMORY_REGION_DESCRIPTOR describing
                               a Physical-to-Virtual Memory mapping. This array
                               must be ended by a zero-filled entry.
**/
VOID
ArmPlatformGetVirtualMemoryMap (
  IN ARM_MEMORY_REGION_DESCRIPTOR** VirtualMemoryMap
  )
{
  UINTN                         Index;
  ARM_MEMORY_REGION_DESCRIPTOR  *VirtualMemoryTable;
  EFI_RESOURCE_ATTRIBUTE_TYPE   ResourceAttributes;

  ResourceAttributes =
    EFI_RESOURCE_ATTRIBUTE_PRESENT |
    EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
    EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
    EFI_RESOURCE_ATTRIBUTE_TESTED;

  BuildResourceDescriptorHob (
    EFI_RESOURCE_SYSTEM_MEMORY,
    ResourceAttributes,
    FixedPcdGet64 (PcdDramBlock2Base),
    FixedPcdGet64 (PcdDramBlock2Size));

  ASSERT (VirtualMemoryMap != NULL);
  Index = 0;

  VirtualMemoryTable = (ARM_MEMORY_REGION_DESCRIPTOR*)AllocatePages
                       (EFI_SIZE_TO_PAGES (sizeof (ARM_MEMORY_REGION_DESCRIPTOR) *
                       MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS));
  if (VirtualMemoryTable == NULL) {
    return;
  }

  // Expansion AXI - SMC Chip Select 0 (NOR Flash)
  VirtualMemoryTable[Index].PhysicalBase    = SGI_EXP_SMC_CS0_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_SMC_CS0_BASE;
  VirtualMemoryTable[Index].Length          = SIZE_64MB;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Expansion AXI - SMC Chip Select 1 (NOR Flash)
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_EXP_SMC_CS1_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_SMC_CS1_BASE;
  VirtualMemoryTable[Index].Length          = SIZE_64MB;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Expansion AXI - SMSC 91X (Ethernet)
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_EXP_SMSC91X_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_SMSC91X_BASE;
  VirtualMemoryTable[Index].Length          = SGI_EXP_SMSC91X_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Expansion AXI - System Peripherals
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_EXP_SYS_PERIPH_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_SYS_PERIPH_BASE;
  VirtualMemoryTable[Index].Length          = SGI_EXP_SYS_PERIPH_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Sub System Peripherals - Generic Watchdog
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_SUBSYS_GENERIC_WDOG_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_SUBSYS_GENERIC_WDOG_BASE;
  VirtualMemoryTable[Index].Length          = SGI_SUBSYS_GENERIC_WDOG_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Sub System Peripherals - GIC-600
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_SUBSYS_GENERIC_GIC_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_SUBSYS_GENERIC_GIC_BASE;
  VirtualMemoryTable[Index].Length          = SGI_SUBSYS_GENERIC_GIC_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Expansion AXI - Platform Peripherals - HDLCD1
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_EXP_PLAT_PERIPH_HDLCD1_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_PLAT_PERIPH_HDLCD1_BASE;
  VirtualMemoryTable[Index].Length          = SGI_EXP_PLAT_PERIPH_HDLCD1_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // Expansion AXI - Platform Peripherals - UART1
  VirtualMemoryTable[++Index].PhysicalBase  = SGI_EXP_PLAT_PERIPH_UART1_BASE;
  VirtualMemoryTable[Index].VirtualBase     = SGI_EXP_PLAT_PERIPH_UART1_BASE;
  VirtualMemoryTable[Index].Length          = SGI_EXP_PLAT_PERIPH_UART1_SZ;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  // DDR - (2GB - 16MB)
  VirtualMemoryTable[++Index].PhysicalBase  = PcdGet64 (PcdSystemMemoryBase);
  VirtualMemoryTable[Index].VirtualBase     = PcdGet64 (PcdSystemMemoryBase);
  VirtualMemoryTable[Index].Length          = PcdGet64 (PcdSystemMemorySize);
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;

  // DDR - Second Block
  VirtualMemoryTable[++Index].PhysicalBase  = PcdGet64 (PcdDramBlock2Base);
  VirtualMemoryTable[Index].VirtualBase     = PcdGet64 (PcdDramBlock2Base);
  VirtualMemoryTable[Index].Length          = PcdGet64 (PcdDramBlock2Size);
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK;

  // PCI Configuration Space
  VirtualMemoryTable[++Index].PhysicalBase  = PcdGet64 (PcdPciExpressBaseAddress);
  VirtualMemoryTable[Index].VirtualBase     = PcdGet64 (PcdPciExpressBaseAddress);
  VirtualMemoryTable[Index].Length          = (FixedPcdGet32 (PcdPciBusMax) -
                                               FixedPcdGet32 (PcdPciBusMin) + 1) *
                                               SIZE_1MB;
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

 // MM Memory Space
  VirtualMemoryTable[++Index].PhysicalBase  = PcdGet64 (PcdMmBufferBase);
  VirtualMemoryTable[Index].VirtualBase     = PcdGet64 (PcdMmBufferBase);
  VirtualMemoryTable[Index].Length          = PcdGet64 (PcdMmBufferSize);
  VirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED;

  // End of Table
  VirtualMemoryTable[++Index].PhysicalBase  = 0;
  VirtualMemoryTable[Index].VirtualBase     = 0;
  VirtualMemoryTable[Index].Length          = 0;
  VirtualMemoryTable[Index].Attributes      = (ARM_MEMORY_REGION_ATTRIBUTES)0;

  ASSERT ((Index + 1) <= MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS);
  *VirtualMemoryMap = VirtualMemoryTable;
}
