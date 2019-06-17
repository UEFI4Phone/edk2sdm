/** @file

  Copyright (c) 2014, Applied Micro Curcuit Corporation. All rights reserved.<BR>
  Copyright (c) 2015, Hisilicon Limited. All rights reserved.<BR>
  Copyright (c) 2015, Linaro Limited. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

  This driver is called to initialize the FW part of the PHY in preparation
  for the OS.

**/

#include <Guid/ShellVariableGuid.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>

#include <PiDxe.h>
#include <Guid/EventGroup.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/AcpiAml.h>

#include <Protocol/HisiBoardNicProtocol.h>

// Turn on debug message by enabling below define
//#define ACPI_DEBUG

#ifdef ACPI_DEBUG
#define DBG(arg...) DEBUG((EFI_D_ERROR,## arg))
#else
#define DBG(arg...)
#endif

#define EFI_ACPI_MAX_NUM_TABLES         20
#define DSDT_SIGNATURE                  0x54445344

#define D03_ACPI_ETH_ID                     "HISI00C2"

#define ACPI_ETH_MAC_KEY                "local-mac-address"

#define PREFIX_VARIABLE_NAME            L"MAC"
#define PREFIX_VARIABLE_NAME_COMPAT     L"RGMII_MAC"
#define MAC_MAX_LEN                     30

EFI_STATUS GetEnvMac(
  IN          UINTN    MacNextID,
  IN OUT      UINT8    *MacBuffer)
{
  EFI_MAC_ADDRESS Mac;
  EFI_STATUS Status;
  HISI_BOARD_NIC_PROTOCOL *OemNic = NULL;

  Status = gBS->LocateProtocol(&gHisiBoardNicProtocolGuid, NULL, (VOID **)&OemNic);
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[%a]:[%dL] LocateProtocol failed %r\n", __FUNCTION__, __LINE__, Status));
    return Status;
  }

  Status = OemNic->GetMac(&Mac, MacNextID);
  if(EFI_ERROR(Status))
  {
    DEBUG((EFI_D_ERROR, "[%a]:[%dL] GetMac failed %r\n", __FUNCTION__, __LINE__, Status));
    return Status;
  }

  CopyMem (MacBuffer, &Mac, 6);
  DEBUG((EFI_D_ERROR, "Port %d MAC %02x:%02x:%02x:%02x:%02x:%02x\n",
        MacNextID,
        MacBuffer[0],
        MacBuffer[1],
        MacBuffer[2],
        MacBuffer[3],
        MacBuffer[4],
        MacBuffer[5]
        ));

  return EFI_SUCCESS;
}

EFI_STATUS _SearchReplacePackageMACAddress(
  IN EFI_ACPI_SDT_PROTOCOL  *AcpiTableProtocol,
  IN EFI_ACPI_HANDLE        ChildHandle,
  IN UINTN                  Level,
  IN OUT BOOLEAN            *Found,
  IN UINTN                  MacNextID)
{
  // ASL template for ethernet driver:
/*
 *   Name (_DSD, Package () {
 *   ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
 *   Package () {
 *     Package (2) {"mac-address", Package (6) { 00, 11, 22, 33, 44, 55 }}
 *     Package (2) {"phy-channel", 0},
 *     Package (2) {"phy-mode", "rgmii"},
 *     Package (2) {"max-transfer-unit", 0x5dc},   // MTU of 1500
 *     Package (2) {"max-speed", 0x3e8},            // 1000 Mbps
 *   }
 * })
 */
  EFI_STATUS          Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CONST UINT8         *Data;
  CONST VOID          *Buffer;
  UINTN               DataSize;
  UINTN               Count;
  EFI_ACPI_HANDLE     CurrentHandle;
  EFI_ACPI_HANDLE     NextHandle;
  UINT8               MACBuffer[MAC_MAX_LEN];

  DBG("In Level:%d\n", Level);
  Status = EFI_SUCCESS;
  for (CurrentHandle = NULL; ;) {
    Status = AcpiTableProtocol->GetChild(ChildHandle, &CurrentHandle);
    if (Level != 3 && (EFI_ERROR(Status) || CurrentHandle == NULL))
       break;

    Status = AcpiTableProtocol->GetOption(CurrentHandle, 0, &DataType, &Buffer, &DataSize);
    Data = Buffer;
    DBG("_DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X\n",
        DataSize, Data[0], DataSize > 1 ? Data[1] : 0);

    if (Level < 2 && Data[0] != AML_PACKAGE_OP)
      continue;

    if (Level == 2 && Data[0] == AML_STRING_PREFIX) {
      Status = AcpiTableProtocol->GetOption(CurrentHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      DBG("  _DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X\n",
              DataSize, Data[0], DataSize > 1 ? Data[1] : 0);

      Data = Buffer;
      if (DataType != EFI_ACPI_DATA_TYPE_STRING
              || AsciiStrCmp((CHAR8 *) Data, ACPI_ETH_MAC_KEY) != 0)
        continue;

      DBG("_DSD Key Type %d. Found MAC address key\n", DataType);

      //
      // We found the node.
      //
      *Found = TRUE;
      continue;
    }

    if (Level == 3 && *Found) {

      //Update the MAC
      Status = GetEnvMac(MacNextID, MACBuffer);
      if (EFI_ERROR(Status))
        break;

      for (Count = 0; Count < 6; Count++) {
        Status = AcpiTableProtocol->GetOption(CurrentHandle, 1, &DataType, &Buffer, &DataSize);
        if (EFI_ERROR(Status))
          break;

        Data = Buffer;
        DBG("    _DSD Child Subnode Store Op Code 0x%02X 0x%02X %02X DataType 0x%X\n",
            DataSize, Data[0], DataSize > 1 ? Data[1] : 0, DataType);

        if (DataType != EFI_ACPI_DATA_TYPE_UINT)
          break;

        // only need one byte.
        // FIXME: Assume the CPU is little endian
        Status = AcpiTableProtocol->SetOption(CurrentHandle, 1, (VOID *)&MACBuffer[Count], sizeof(UINT8));
        if (EFI_ERROR(Status))
          break;
        Status = AcpiTableProtocol->GetChild(ChildHandle, &CurrentHandle);
        if (EFI_ERROR(Status) || CurrentHandle == NULL)
          break;
      }
      break;
    }

    if (Level > 3)
      break;

    //Search next package
    AcpiTableProtocol->Open((VOID *) Buffer, &NextHandle);
    Status = _SearchReplacePackageMACAddress(AcpiTableProtocol, NextHandle, Level + 1, Found, MacNextID);
    AcpiTableProtocol->Close(NextHandle);
    if (!EFI_ERROR(Status))
      break;
  }

  return Status;
}

EFI_STATUS SearchReplacePackageMACAddress(
  IN EFI_ACPI_SDT_PROTOCOL  *AcpiTableProtocol,
  IN EFI_ACPI_HANDLE        ChildHandle,
  IN UINTN                  MacNextID)
{
  BOOLEAN Found = FALSE;
  UINTN Level = 0;

  return _SearchReplacePackageMACAddress(AcpiTableProtocol, ChildHandle, Level, &Found, MacNextID);
}

EFI_STATUS
GetEthID (
  EFI_ACPI_SDT_PROTOCOL   *AcpiTableProtocol,
  EFI_ACPI_HANDLE         ChildHandle,
  UINTN                   *EthID
  )
{
  EFI_STATUS Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CHAR8               Data[5];
  CONST VOID          *Buffer;
  UINTN               DataSize;

  // Get NameString ETHx
  Status = AcpiTableProtocol->GetOption (ChildHandle, 1, &DataType, &Buffer, &DataSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "[%a:%d] Get NameString failed: %r\n", __FUNCTION__, __LINE__, Status));
    return Status;
  }

  CopyMem (Data, Buffer, 4);
  DBG("Size %p Data %02x %02x %02x %02x\n", DataSize, Data[0], Data[1], Data[2], Data[3]);

  Data[4] = '\0';
  if (DataSize != 4 ||
      AsciiStrnCmp ("ETH", Data, 3) != 0 ||
      Data[3] > '9' || Data[3] < '0') {
    DEBUG ((EFI_D_ERROR, "[%a:%d] The NameString %a is not ETHn\n", __FUNCTION__, __LINE__, Data));
    return EFI_INVALID_PARAMETER;
  }

  *EthID = Data[3] - '0';
  return EFI_SUCCESS;
}

EFI_STATUS ProcessDSDTDevice (
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE ChildHandle)
{
  EFI_STATUS          Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CONST UINT8         *Data;
  CONST VOID          *Buffer;
  UINTN               DataSize;
  EFI_ACPI_HANDLE     DevHandle;
  INTN                Found = 0;
  UINTN               MacNextID;

  Status = AcpiTableProtocol->GetOption(ChildHandle, 0, &DataType, &Buffer, &DataSize);
  if (EFI_ERROR(Status))
    return EFI_SUCCESS;

  Data = Buffer;
  //
  // Skip all non-device type
  //
  if (DataSize != 2 || Data[0] != AML_EXT_OP || Data[1] != AML_EXT_DEVICE_OP)
    return EFI_SUCCESS;

  //
  // Walk the device type node
  //
  for (DevHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(ChildHandle, &DevHandle);
    if (EFI_ERROR(Status) || DevHandle == NULL)
      break;

    //
    // Search for _HID with Ethernet ID
    //
    Status = AcpiTableProtocol->GetOption(DevHandle, 0, &DataType, &Buffer, &DataSize);
    if (EFI_ERROR(Status))
      break;

    Data = Buffer;
    DBG("Data Type 0x%02X %02X\n", Data[0], DataSize > 1 ? Data[1] : 0);
    if (DataSize == 1 && Data[0] == AML_NAME_OP) {
      Status = AcpiTableProtocol->GetOption(DevHandle, 1, &DataType, &Buffer, &DataSize);
      if (EFI_ERROR(Status))
        break;

      Data = Buffer;
      if (DataType == EFI_ACPI_DATA_TYPE_NAME_STRING) {
        if (AsciiStrnCmp((CHAR8 *) Data, "_HID", 4) == 0) {
          EFI_ACPI_HANDLE ValueHandle;

          Status = AcpiTableProtocol->GetOption(DevHandle, 2, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;

          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          AcpiTableProtocol->Open((VOID *) Buffer, &ValueHandle);
          Status = AcpiTableProtocol->GetOption(ValueHandle, 1, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          DBG("[%a:%d] - _HID = %a\n", __FUNCTION__, __LINE__, Data);

          if (EFI_ERROR(Status) ||
              DataType != EFI_ACPI_DATA_TYPE_STRING ||
              (AsciiStrCmp((CHAR8 *) Data, D03_ACPI_ETH_ID) != 0)) {
            AcpiTableProtocol->Close(ValueHandle);
            Found = 0;
            continue;
          }

          DBG("Found Ethernet device\n");
          AcpiTableProtocol->Close(ValueHandle);
          Status = GetEthID (AcpiTableProtocol, ChildHandle, &MacNextID);
          if (EFI_ERROR (Status)) {
            continue;
          }
          Found = 1;
        } else if (Found == 1 && AsciiStrnCmp((CHAR8 *) Data, "_DSD", 4) == 0) {
          //
          // Patch MAC address for open source kernel
          //
          EFI_ACPI_HANDLE    PkgHandle;
          Status = AcpiTableProtocol->GetOption(DevHandle, 2, &DataType, &Buffer, &DataSize);
          if (EFI_ERROR(Status))
            break;

          if (DataType != EFI_ACPI_DATA_TYPE_CHILD)
            continue;

          //
          // Open package data
          //
          AcpiTableProtocol->Open((VOID *) Buffer, &PkgHandle);
          Status = AcpiTableProtocol->GetOption(PkgHandle, 0, &DataType, &Buffer, &DataSize);

          Data = Buffer;
          DBG("_DSD Subnode Store Op Code 0x%02X %02X\n",
                Data[0], DataSize > 1 ? Data[1] : 0);

          //
          // Walk the _DSD node
          //
          if (DataSize == 1 && Data[0] == AML_PACKAGE_OP)
            Status = SearchReplacePackageMACAddress(AcpiTableProtocol, PkgHandle, MacNextID);

          AcpiTableProtocol->Close(PkgHandle);
        }
      }
    }
  }

  return EFI_SUCCESS;
}


BOOLEAN
IsSbScope (
  EFI_ACPI_SDT_PROTOCOL   *AcpiTableProtocol,
  EFI_ACPI_HANDLE         ChildHandle
  )
{
  EFI_STATUS          Status;
  EFI_ACPI_DATA_TYPE  DataType;
  CONST UINT8         *Data;
  CONST VOID          *Buffer;
  UINTN               DataSize;

  Status = AcpiTableProtocol->GetOption (ChildHandle, 0, &DataType, &Buffer, &DataSize);
  if (EFI_ERROR(Status)) return FALSE;

  Data = Buffer;
  if (DataSize != 1 || Data[0] != AML_SCOPE_OP) {
    return FALSE;
  }

  return TRUE;
}

EFI_STATUS ProcessDSDTChild(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE ChildHandle)
{
  EFI_STATUS          Status;
  EFI_ACPI_HANDLE     DevHandle;

  // Check Scope(_SB) at first
  if (!IsSbScope (AcpiTableProtocol, ChildHandle)) {
    return ProcessDSDTDevice (AcpiTableProtocol, ChildHandle);
  }

  for (DevHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild (ChildHandle, &DevHandle);
    if (EFI_ERROR(Status) || DevHandle == NULL) {
      break;
    }

    ProcessDSDTDevice (AcpiTableProtocol, DevHandle);
  }

  return EFI_SUCCESS;
}

static EFI_STATUS ProcessDSDT(
  EFI_ACPI_SDT_PROTOCOL *AcpiTableProtocol,
  EFI_ACPI_HANDLE TableHandle)
{
  EFI_STATUS              Status;
  EFI_ACPI_HANDLE         ChildHandle;
  //
  // Parse table for device type
  DBG ("[%a:%d] - TableHandle=%p\n", __FUNCTION__, __LINE__, TableHandle);
  for (ChildHandle = NULL; ; ) {
    Status = AcpiTableProtocol->GetChild(TableHandle, &ChildHandle);
    DBG ("[%a:%d] - Child=%p, %r\n", __FUNCTION__, __LINE__, ChildHandle, Status);
    if (EFI_ERROR(Status))
      break;
    if (ChildHandle == NULL)
      break;

    ProcessDSDTChild(AcpiTableProtocol, ChildHandle);
  }

  return EFI_SUCCESS;
}

STATIC
VOID
AcpiCheckSum (
  IN OUT  EFI_ACPI_SDT_HEADER *Table
  )
{
  UINTN ChecksumOffset;
  UINT8 *Buffer;

  ChecksumOffset = OFFSET_OF (EFI_ACPI_DESCRIPTION_HEADER, Checksum);
  Buffer = (UINT8 *)Table;

  //
  // set checksum to 0 first
  //
  Buffer[ChecksumOffset] = 0;

  //
  // Update checksum value
  //
  Buffer[ChecksumOffset] = CalculateCheckSum8 (Buffer, Table->Length);
}

EFI_STATUS EthMacInit(void)
{
  EFI_STATUS              Status;
  EFI_ACPI_SDT_PROTOCOL   *AcpiTableProtocol;
  EFI_ACPI_SDT_HEADER     *Table;
  EFI_ACPI_TABLE_VERSION  TableVersion;
  UINTN                   TableKey;
  EFI_ACPI_HANDLE         TableHandle;
  UINTN                   i;

  DEBUG ((EFI_D_ERROR, "Updating Ethernet MAC in ACPI DSDT...\n"));

  //
  // Find the AcpiTable protocol
  Status = gBS->LocateProtocol(&gEfiAcpiSdtProtocolGuid, NULL, (VOID**) &AcpiTableProtocol);
  if (EFI_ERROR(Status)) {
    DBG("Unable to locate ACPI table protocol\n");
    return EFI_SUCCESS;
  }

  //
  // Search for DSDT Table
  for (i = 0; i < EFI_ACPI_MAX_NUM_TABLES; i++) {
    Status = AcpiTableProtocol->GetAcpiTable(i, &Table, &TableVersion, &TableKey);
    if (EFI_ERROR(Status))
      break;
    if (Table->Signature != DSDT_SIGNATURE)
      continue;

    Status = AcpiTableProtocol->OpenSdt(TableKey, &TableHandle);
    if (EFI_ERROR(Status))
      break;

    ProcessDSDT(AcpiTableProtocol, TableHandle);

    AcpiTableProtocol->Close(TableHandle);
    AcpiCheckSum (Table);
  }

  return EFI_SUCCESS;
}
