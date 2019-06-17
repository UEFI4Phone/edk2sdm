/** @file
*
*  Copyright (c) 2018, ARM Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#include <Library/AcpiLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <SgiPlatform.h>

VOID
InitVirtioDevices (
  VOID
  );

EFI_STATUS
EFIAPI
ArmSgiPkgEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS              Status;
  VOID                    *SystemIdHob;
  SGI_PLATFORM_DESCRIPTOR *HobData;
  UINT32                  ConfigId;
  UINT32                  PartNum;

  SystemIdHob = GetFirstGuidHob (&gArmSgiPlatformIdDescriptorGuid);
  if (SystemIdHob == NULL) {
    DEBUG ((DEBUG_ERROR, "System ID HOB is NULL\n"));
    return EFI_INVALID_PARAMETER;
  }

  HobData = (SGI_PLATFORM_DESCRIPTOR *)GET_GUID_HOB_DATA (SystemIdHob);

  PartNum = HobData->PlatformId;
  ConfigId = HobData->ConfigId;

  if ((PartNum == SGI575_PART_NUM) && (ConfigId == SGI575_CONF_NUM)) {
    Status = LocateAndInstallAcpiFromFv (&gSgi575AcpiTablesFileGuid);
  } else if ((PartNum == RD_N1E1_EDGE_PART_NUM) &&
             (ConfigId == RD_N1_EDGE_CONF_ID)) {
    Status = LocateAndInstallAcpiFromFv (&gRdN1EdgeAcpiTablesFileGuid);
  } else if ((PartNum == RD_N1E1_EDGE_PART_NUM) &&
             (ConfigId == RD_E1_EDGE_CONF_ID)) {
    Status = LocateAndInstallAcpiFromFv (&gRdE1EdgeAcpiTablesFileGuid);
  } else {
    Status = EFI_UNSUPPORTED;
  }

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "%a: Failed to install ACPI tables\n", __FUNCTION__));
    return Status;
  }

  InitVirtioDevices ();

  return Status;
}
