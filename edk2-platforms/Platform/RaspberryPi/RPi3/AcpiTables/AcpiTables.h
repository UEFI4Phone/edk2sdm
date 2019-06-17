/** @file
 *
 *  RPi3 defines for constructing ACPI tables
 *
 *  Copyright (c) 2018, Andrei Warkentin <andrey.warkentin@gmail.com>
 *  Copyright (c) Microsoft Corporation. All rights reserved.
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#ifndef __ACPITABLES_H__
#define __ACPITABLES_H__

#include <IndustryStandard/Acpi50.h>

#define EFI_ACPI_OEM_ID                       {'M','C','R','S','F','T'} // OEMID 6 bytes long
#define EFI_ACPI_OEM_TABLE_ID                 SIGNATURE_64 ('R','P','I','3','E','D','K','2') // OEM table id 8 bytes long
#define EFI_ACPI_OEM_REVISION                 0x02000820
#define EFI_ACPI_CREATOR_ID                   SIGNATURE_32 ('R','P','I','3')
#define EFI_ACPI_CREATOR_REVISION             0x00000097

#define EFI_ACPI_VENDOR_ID                    SIGNATURE_32 ('M','S','F','T')
#define EFI_ACPI_CSRT_REVISION                0x00000005
#define EFI_ACPI_CSRT_DEVICE_ID_DMA           0x00000009 // Fixed id
#define EFI_ACPI_CSRT_RESOURCE_ID_IN_DMA_GRP  0x0 // Count up from 0

#define RPI3_DMA_CHANNEL_COUNT                10 // All 10 DMA channels are listed, including the reserved ones
#define RPI3_DMA_USED_CHANNEL_COUNT           5  // Use 5 DMA channels

#define EFI_ACPI_5_0_CSRT_REVISION            0x00000000

typedef enum
{
  EFI_ACPI_CSRT_RESOURCE_TYPE_RESERVED,           // 0
  EFI_ACPI_CSRT_RESOURCE_TYPE_INTERRUPT,          // 1
  EFI_ACPI_CSRT_RESOURCE_TYPE_TIMER,              // 2
  EFI_ACPI_CSRT_RESOURCE_TYPE_DMA,                // 3
  EFI_ACPI_CSRT_RESOURCE_TYPE_CACHE,              // 4
}
CSRT_RESOURCE_TYPE;

typedef enum
{
  EFI_ACPI_CSRT_RESOURCE_SUBTYPE_DMA_CHANNEL,     // 0
  EFI_ACPI_CSRT_RESOURCE_SUBTYPE_DMA_CONTROLLER   // 1
}
CSRT_DMA_SUBTYPE;

//------------------------------------------------------------------------
// CSRT Resource Group header 24 bytes long
//------------------------------------------------------------------------
typedef struct
{
  UINT32 Length;                  // Length
  UINT32 VendorID;                // 4 bytes
  UINT32 SubVendorId;             // 4 bytes
  UINT16 DeviceId;                // 2 bytes
  UINT16 SubdeviceId;             // 2 bytes
  UINT16 Revision;                // 2 bytes
  UINT16 Reserved;                // 2 bytes
  UINT32 SharedInfoLength;        // 4 bytes
} EFI_ACPI_5_0_CSRT_RESOURCE_GROUP_HEADER;

//------------------------------------------------------------------------
// CSRT Resource Descriptor 12 bytes total
//------------------------------------------------------------------------
typedef struct
{
  UINT32 Length;                  // 4 bytes
  UINT16 ResourceType;            // 2 bytes
  UINT16 ResourceSubType;         // 2 bytes
  UINT32 UID;                     // 4 bytes
} EFI_ACPI_5_0_CSRT_RESOURCE_DESCRIPTOR_HEADER;

#endif // __ACPITABLES_H__
