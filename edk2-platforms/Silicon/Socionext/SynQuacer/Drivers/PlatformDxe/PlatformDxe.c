/** @file
  SynQuacer DXE platform driver.

  Copyright (c) 2017, Linaro, Ltd. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include "PlatformDxe.h"

UINT64                            mHiiSettingsVal;
SYNQUACER_PLATFORM_VARSTORE_DATA  *mHiiSettings;

typedef struct {
  VENDOR_DEVICE_PATH              VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL        End;
} HII_VENDOR_DEVICE_PATH;

STATIC HII_VENDOR_DEVICE_PATH     mPlatformDxeHiiVendorDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    SYNQUACER_PLATFORM_FORMSET_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};

STATIC EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR mNetsecDesc[] = {
  {
    ACPI_ADDRESS_SPACE_DESCRIPTOR,                    // Desc
    sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) - 3,   // Len
    ACPI_ADDRESS_SPACE_TYPE_MEM,                      // ResType
    0,                                                // GenFlag
    0,                                                // SpecificFlag
    32,                                               // AddrSpaceGranularity
    SYNQUACER_NETSEC1_BASE,                           // AddrRangeMin
    SYNQUACER_NETSEC1_BASE +
    SYNQUACER_NETSEC1_BASE_SZ - 1,                    // AddrRangeMax
    0,                                                // AddrTranslationOffset
    SYNQUACER_NETSEC1_BASE_SZ,                        // AddrLen
  }, {
    ACPI_ADDRESS_SPACE_DESCRIPTOR,                    // Desc
    sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) - 3,   // Len
    ACPI_ADDRESS_SPACE_TYPE_MEM,                      // ResType
    0,                                                // GenFlag
    0,                                                // SpecificFlag
    32,                                               // AddrSpaceGranularity
    FixedPcdGet32 (PcdNetsecEepromBase),              // AddrRangeMin
    FixedPcdGet32 (PcdNetsecEepromBase) +
    SYNQUACER_EEPROM_BASE_SZ - 1,                     // AddrRangeMax
    0,                                                // AddrTranslationOffset
    SYNQUACER_EEPROM_BASE_SZ,                         // AddrLen
  }, {
    ACPI_ADDRESS_SPACE_DESCRIPTOR,                    // Desc
    sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) - 3,   // Len
    ACPI_ADDRESS_SPACE_TYPE_MEM,                      // ResType
    0,                                                // GenFlag
    0,                                                // SpecificFlag
    32,                                               // AddrSpaceGranularity
    FixedPcdGet32 (PcdNetsecPhyAddress),              // AddrRangeMin
    FixedPcdGet32 (PcdNetsecPhyAddress),              // AddrRangeMax
    0,                                                // AddrTranslationOffset
    1,                                                // AddrLen
  }, {
    ACPI_END_TAG_DESCRIPTOR                           // Desc
  }
};

STATIC EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR mI2c0Desc[] = {
  {
    ACPI_ADDRESS_SPACE_DESCRIPTOR,                    // Desc
    sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) - 3,   // Len
    ACPI_ADDRESS_SPACE_TYPE_MEM,                      // ResType
    0,                                                // GenFlag
    0,                                                // SpecificFlag
    32,                                               // AddrSpaceGranularity
    SYNQUACER_I2C0_BASE,                              // AddrRangeMin
    SYNQUACER_I2C0_BASE + SYNQUACER_I2C0_SIZE - 1,    // AddrRangeMax
    0,                                                // AddrTranslationOffset
    SYNQUACER_I2C0_SIZE,                              // AddrLen
  }, {
    ACPI_END_TAG_DESCRIPTOR                           // Desc
  }
};

STATIC EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR mI2c1Desc[] = {
  {
    ACPI_ADDRESS_SPACE_DESCRIPTOR,                    // Desc
    sizeof (EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR) - 3,   // Len
    ACPI_ADDRESS_SPACE_TYPE_MEM,                      // ResType
    0,                                                // GenFlag
    0,                                                // SpecificFlag
    32,                                               // AddrSpaceGranularity
    SYNQUACER_I2C1_BASE,                              // AddrRangeMin
    SYNQUACER_I2C1_BASE + SYNQUACER_I2C1_SIZE - 1,    // AddrRangeMax
    0,                                                // AddrTranslationOffset
    SYNQUACER_I2C1_SIZE,                              // AddrLen
  }, {
    ACPI_END_TAG_DESCRIPTOR                           // Desc
  }
};

STATIC
EFI_STATUS
RegisterDevice (
  IN  EFI_GUID                            *TypeGuid,
  IN  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR   *Desc,
  OUT EFI_HANDLE                          *Handle
  )
{
  NON_DISCOVERABLE_DEVICE             *Device;
  EFI_STATUS                          Status;

  Device = (NON_DISCOVERABLE_DEVICE *)AllocateZeroPool (sizeof (*Device));
  if (Device == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Device->Type = TypeGuid;
  Device->DmaType = NonDiscoverableDeviceDmaTypeNonCoherent;
  Device->Resources = Desc;

  Status = gBS->InstallMultipleProtocolInterfaces (Handle,
                  &gEdkiiNonDiscoverableDeviceProtocolGuid, Device,
                  NULL);
  if (EFI_ERROR (Status)) {
    goto FreeDevice;
  }
  return EFI_SUCCESS;

FreeDevice:
  FreePool (Device);

  return Status;
}

#define SMMU_SCR0                         0x0
#define SMMU_SCR0_SHCFG_INNER             (0x2 << 22)
#define SMMU_SCR0_MTCFG                   (0x1 << 20)
#define SMMU_SCR0_MEMATTR_INNER_OUTER_WB  (0xf << 16)

STATIC
VOID
SmmuEnableCoherentDma (
  VOID
  )
{
  //
  // The SCB SMMU (MMU-500) is shared between the NETSEC and eMMC devices, and
  // is configured in passthrough mode by default. Let's set the global memory
  // type override as well, so that all memory accesses by these devices are
  // inner shareable inner/outer writeback cacheable.
  //
  MmioOr32 (SYNQUACER_SCB_SMMU_BASE + SMMU_SCR0,
    SMMU_SCR0_SHCFG_INNER | SMMU_SCR0_MTCFG | SMMU_SCR0_MEMATTR_INNER_OUTER_WB);
}

#define MMIO_TIMER_CNTFRQ_OFFSET          0x10

STATIC
VOID
SetMmioTimerFrequency (
  VOID
  )
{
  //
  // Initialize the CNTFRQ field of the first non-secure MMIO timer frame.
  // This field should be a read-only alias of the global frequency register
  // but in reality, it is a separate field that needs to be set explicitly.
  //
  MmioWrite32 (SYNQUACER_MMIO_TIMER_CNT_BASE0 + MMIO_TIMER_CNTFRQ_OFFSET,
    ArmGenericTimerGetTimerFreq ());
}

STATIC
EFI_STATUS
InstallHiiPages (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_HII_HANDLE                  HiiHandle;
  EFI_HANDLE                      DriverHandle;

  DriverHandle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (&DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mPlatformDxeHiiVendorDevicePath,
                  NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  HiiHandle = HiiAddPackages (&gSynQuacerPlatformFormSetGuid,
                              DriverHandle,
                              PlatformDxeStrings,
                              PlatformDxeHiiBin,
                              NULL);

  if (HiiHandle == NULL) {
    gBS->UninstallMultipleProtocolInterfaces (DriverHandle,
           &gEfiDevicePathProtocolGuid,
           &mPlatformDxeHiiVendorDevicePath,
           NULL);
    return EFI_OUT_OF_RESOURCES;
  }
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
EnableSettingsForm (
  VOID
  )
{
  EFI_STATUS                        Status;
  UINTN                             VarSize;
  SYNQUACER_PLATFORM_VARSTORE_DATA  Settings;

  VarSize = sizeof (Settings);
  Status = gRT->GetVariable (SYNQUACER_PLATFORM_VARIABLE_NAME,
                  &gSynQuacerPlatformFormSetGuid, NULL, &VarSize, &Settings);
  if (Status == EFI_NOT_FOUND) {
    //
    // Variable does not exist yet - create it
    //
    SetMem (&Settings, sizeof (Settings), 0);
    Status = gRT->SetVariable (SYNQUACER_PLATFORM_VARIABLE_NAME,
                    &gSynQuacerPlatformFormSetGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    sizeof (Settings), &Settings);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_WARN, "%a: EfiSetVariable failed - %r\n", __FUNCTION__,
        Status));
      return Status;
    }
  } else if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "%a: EfiGetVariable failed - %r\n", __FUNCTION__,
      Status));
    return Status;
  }

  return InstallHiiPages ();
}

EFI_STATUS
EFIAPI
PlatformDxeEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS                      Status;
  VOID                            *Dtb;
  UINTN                           DtbSize;
  EFI_HANDLE                      Handle;

  mHiiSettingsVal = PcdGet64 (PcdPlatformSettings);
  mHiiSettings = (SYNQUACER_PLATFORM_VARSTORE_DATA *)&mHiiSettingsVal;

  if (mHiiSettings->AcpiPref == ACPIPREF_DT) {
    Dtb = NULL;
    Status = DtPlatformLoadDtb (&Dtb, &DtbSize);
    if (!EFI_ERROR (Status)) {
      Status = gBS->InstallConfigurationTable (&gFdtTableGuid, Dtb);
    }
    if (EFI_ERROR (Status)) {
       DEBUG ((DEBUG_ERROR,
        "%a: failed to install FDT configuration table - %r\n", __FUNCTION__,
        Status));
    }
  } else {
    //
    // ACPI was selected: install the gEdkiiPlatformHasAcpiGuid GUID as a
    // NULL protocol to unlock dispatch of ACPI related drivers.
    //
    Status = gBS->InstallMultipleProtocolInterfaces (&ImageHandle,
                    &gEdkiiPlatformHasAcpiGuid, NULL, NULL);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR,
        "%a: failed to install gEdkiiPlatformHasAcpiGuid as a protocol\n",
        __FUNCTION__));
    }
  }

  Handle = NULL;
  Status = RegisterDevice (&gNetsecNonDiscoverableDeviceGuid, mNetsecDesc,
             &Handle);
  ASSERT_EFI_ERROR (Status);

  Handle = NULL;
  Status = RegisterDevice (&gSynQuacerNonDiscoverableRuntimeI2cMasterGuid,
             mI2c0Desc, &Handle);
  ASSERT_EFI_ERROR (Status);

  //
  // Install the PCF8563 I2C Master protocol on this handle so the RTC driver
  // can identify it as the I2C master it can invoke directly, rather than
  // through the I2C driver stack (which cannot be used at runtime)
  //
  Status = gBS->InstallProtocolInterface (&Handle,
                  &gPcf8563RealTimeClockLibI2cMasterProtocolGuid,
                  EFI_NATIVE_INTERFACE, NULL);
  ASSERT_EFI_ERROR (Status);

  Handle = NULL;
  Status = RegisterDevice (&gSynQuacerNonDiscoverableI2cMasterGuid, mI2c1Desc,
             &Handle);
  ASSERT_EFI_ERROR (Status);

  //
  // Install the g96BoardsI2c0MasterGuid GUID onto the same handle,
  // identifying I2C #1 on our SoC as I2C #0 on the 96boards low speed connector
  //
  Status = gBS->InstallProtocolInterface (&Handle,
                  &g96BoardsI2c0MasterGuid,
                  EFI_NATIVE_INTERFACE, NULL);
  ASSERT_EFI_ERROR (Status);

  SmmuEnableCoherentDma ();
  SetMmioTimerFrequency ();

  Status = RegisterPcieNotifier ();
  ASSERT_EFI_ERROR (Status);

  Status = EnableSettingsForm ();
  ASSERT_EFI_ERROR (Status);

  if (mHiiSettings->EnableEmmc == EMMC_ENABLED) {
    Status = RegisterEmmc ();
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}
