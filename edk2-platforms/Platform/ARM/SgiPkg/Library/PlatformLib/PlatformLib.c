/** @file
*
*  Copyright (c) 2018, ARM Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Library/ArmPlatformLib.h>
#include <Library/BaseLib.h>
#include <Ppi/ArmMpCoreInfo.h>
#include <Ppi/SgiPlatformId.h>

UINT64 NtFwConfigDtBlob;
STATIC SGI_NT_FW_CONFIG_INFO_PPI mNtFwConfigDtInfoPpi;

STATIC ARM_CORE_INFO mCoreInfoTable[] = {
  {
    // Cluster 0, Core 0
    0x0, 0x0,
  },
};

EFI_BOOT_MODE
ArmPlatformGetBootMode (
  VOID
  )
{
  return BOOT_WITH_FULL_CONFIGURATION;
}

RETURN_STATUS
ArmPlatformInitialize (
  IN  UINTN                     MpId
  )
{
  mNtFwConfigDtInfoPpi.NtFwConfigDtAddr = NtFwConfigDtBlob;
  return RETURN_SUCCESS;
}

EFI_STATUS
PrePeiCoreGetMpCoreInfo (
  OUT UINTN                   *CoreCount,
  OUT ARM_CORE_INFO           **ArmCoreTable
  )
{
  *CoreCount = 1;
  *ArmCoreTable = mCoreInfoTable;
  return EFI_SUCCESS;
}

STATIC ARM_MP_CORE_INFO_PPI mMpCoreInfoPpi = {
  PrePeiCoreGetMpCoreInfo
};

EFI_PEI_PPI_DESCRIPTOR gPlatformPpiTable[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gArmMpCoreInfoPpiGuid,
    &mMpCoreInfoPpi
  },
  {
    EFI_PEI_PPI_DESCRIPTOR_PPI,
    &gNtFwConfigDtInfoPpiGuid,
    &mNtFwConfigDtInfoPpi
  }
};

VOID
ArmPlatformGetPlatformPpiList (
  OUT UINTN                   *PpiListSize,
  OUT EFI_PEI_PPI_DESCRIPTOR  **PpiList
  )
{
  *PpiListSize = sizeof (gPlatformPpiTable);
  *PpiList = gPlatformPpiTable;
}
