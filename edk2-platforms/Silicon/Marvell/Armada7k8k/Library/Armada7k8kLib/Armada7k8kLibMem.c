/*******************************************************************************
Copyright (C) 2016 Marvell International Ltd.

Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
 this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.

* Neither the name of Marvell nor the names of its contributors may be
 used to endorse or promote products derived from this software without
 specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*******************************************************************************/

#include <Uefi.h>

#include <IndustryStandard/ArmStdSmc.h>
#include <IndustryStandard/MvSmc.h>

#include <Library/ArmadaSoCDescLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/ArmSmcLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>

#include "Armada7k8kLibMem.h"

// The total number of descriptors, including the final "end-of-table" descriptor.
#define MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS 16

// DDR attributes
#define DDR_ATTRIBUTES_CACHED           ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_WRITE_BACK
#define DDR_ATTRIBUTES_UNCACHED         ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED

STATIC ARM_MEMORY_REGION_DESCRIPTOR mVirtualMemoryTable[MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS];

// Obtain DRAM size basing on register values filled by early firmware.
STATIC
UINT64
GetDramSize (
  IN OUT UINT64 *MemSize
  )
{
  ARM_SMC_ARGS SmcRegs = {0};
  EFI_STATUS Status;

  SmcRegs.Arg0 = MV_SMC_ID_DRAM_SIZE;
  Status = ArmadaSoCAp8xxBaseGet (&SmcRegs.Arg1, 0);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ArmCallSmc (&SmcRegs);

  *MemSize = SmcRegs.Arg0;

  return EFI_SUCCESS;
}

/**
  Return the Virtual Memory Map of your platform

  This Virtual Memory Map is used by MemoryInitPei Module to initialize the MMU on your platform.

  @param[out]   VirtualMemoryMap    Array of ARM_MEMORY_REGION_DESCRIPTOR describing a Physical-to-
                                    Virtual Memory mapping. This array must be ended by a zero-filled
                                    entry

**/
VOID
ArmPlatformGetVirtualMemoryMap (
  IN ARM_MEMORY_REGION_DESCRIPTOR** VirtualMemoryMap
  )
{
  UINTN                         Index = 0;
  UINT64                        MemSize;
  UINT64                        MemLowSize;
  UINT64                        MemHighStart;
  UINT64                        MemHighSize;
  UINT64                        ConfigSpaceBaseAddr;
  EFI_RESOURCE_ATTRIBUTE_TYPE   ResourceAttributes;
  EFI_STATUS                    Status;

  ASSERT (VirtualMemoryMap != NULL);

  ConfigSpaceBaseAddr = FixedPcdGet64 (PcdConfigSpaceBaseAddress);

  // Obtain total memory size from the hardware.
  Status = GetDramSize (&MemSize);
  if (EFI_ERROR (Status)) {
    MemSize = FixedPcdGet64 (PcdSystemMemorySize);
    DEBUG ((DEBUG_ERROR, "Limit total memory size to %d MB\n", MemSize / 1024 / 1024));
  }

  if (DRAM_REMAP_ENABLED) {
    MemLowSize = MIN (DRAM_REMAP_TARGET, MemSize);
    MemHighStart = (UINT64)DRAM_REMAP_TARGET + DRAM_REMAP_SIZE;
    MemHighSize = MemSize - MemLowSize;
  } else {
    MemLowSize = MIN (ConfigSpaceBaseAddr, MemSize);
  }

  ResourceAttributes = (
      EFI_RESOURCE_ATTRIBUTE_PRESENT |
      EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
      EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
      EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
      EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |
      EFI_RESOURCE_ATTRIBUTE_TESTED
  );

  BuildResourceDescriptorHob (
    EFI_RESOURCE_SYSTEM_MEMORY,
    ResourceAttributes,
    FixedPcdGet64 (PcdSystemMemoryBase),
    MemLowSize
    );

  // DDR
  mVirtualMemoryTable[Index].PhysicalBase    = FixedPcdGet64 (PcdSystemMemoryBase);
  mVirtualMemoryTable[Index].VirtualBase     = FixedPcdGet64 (PcdSystemMemoryBase);
  mVirtualMemoryTable[Index].Length          = MemLowSize;
  mVirtualMemoryTable[Index].Attributes      = DDR_ATTRIBUTES_CACHED;

  // Configuration space
  mVirtualMemoryTable[++Index].PhysicalBase  = ConfigSpaceBaseAddr;
  mVirtualMemoryTable[Index].VirtualBase     = ConfigSpaceBaseAddr;
  mVirtualMemoryTable[Index].Length          = SIZE_4GB - ConfigSpaceBaseAddr;
  mVirtualMemoryTable[Index].Attributes      = ARM_MEMORY_REGION_ATTRIBUTE_DEVICE;

  if (MemSize > MemLowSize) {
    //
    // If we have more than MemLowSize worth of DRAM, the remainder will be
    // mapped at the top of the remapped window.
    //
    mVirtualMemoryTable[++Index].PhysicalBase  = MemHighStart;
    mVirtualMemoryTable[Index].VirtualBase     = MemHighStart;
    mVirtualMemoryTable[Index].Length          = MemHighSize;
    mVirtualMemoryTable[Index].Attributes      = DDR_ATTRIBUTES_CACHED;

    BuildResourceDescriptorHob (
      EFI_RESOURCE_SYSTEM_MEMORY,
      ResourceAttributes,
      MemHighStart,
      MemHighSize
      );
  }

  // End of Table
  mVirtualMemoryTable[++Index].PhysicalBase  = 0;
  mVirtualMemoryTable[Index].VirtualBase     = 0;
  mVirtualMemoryTable[Index].Length          = 0;
  mVirtualMemoryTable[Index].Attributes      = 0;

  ASSERT((Index + 1) <= MAX_VIRTUAL_MEMORY_MAP_DESCRIPTORS);

  *VirtualMemoryMap = mVirtualMemoryTable;
}
