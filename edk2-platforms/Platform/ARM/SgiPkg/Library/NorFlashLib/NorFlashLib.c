/** @file

  Copyright (c) 2018, ARM Ltd. All rights reserved.

  SPDX-License-Identifier: BSD-2-Clause-Patent

 **/

#include <PiDxe.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/NorFlashPlatformLib.h>
#include <SgiPlatform.h>

STATIC NOR_FLASH_DESCRIPTION mNorFlashDevices[] = {
  {
    SGI_EXP_SMC_CS0_BASE,
    SGI_EXP_SMC_CS0_BASE,
    SIZE_256KB * 256,
    SIZE_256KB,
  },
  {
    SGI_EXP_SMC_CS1_BASE,
    SGI_EXP_SMC_CS1_BASE,
    SIZE_256KB * 256,
    SIZE_256KB,
  },
};

EFI_STATUS
NorFlashPlatformInitialization (
  VOID
  )
{
  UINT64 SysRegFlash;

  SysRegFlash = SGI_EXP_SYSPH_SYSTEM_REGISTERS + SGI_SYSPH_SYS_REG_FLASH;
  MmioOr32 (SysRegFlash, SGI_SYSPH_SYS_REG_FLASH_RWEN);
  return EFI_SUCCESS;
}

EFI_STATUS
NorFlashPlatformGetDevices (
  OUT NOR_FLASH_DESCRIPTION   **NorFlashDevices,
  OUT UINT32                  *Count
  )
{
  if ((NorFlashDevices == NULL) || (Count == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  *NorFlashDevices = mNorFlashDevices;
  *Count = ARRAY_SIZE (mNorFlashDevices);
  return EFI_SUCCESS;
}
