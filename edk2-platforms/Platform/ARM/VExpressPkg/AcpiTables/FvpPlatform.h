/** @file
*
*  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
*  Copyright (c) 2015, Hisilicon Limited. All rights reserved.
*  Copyright (c) 2015, Linaro Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
*  Based on the files under ArmPlatformPkg/ArmJunoPkg/AcpiTables/
*
**/


#ifndef _FVP_PLATFORM_H_
#define _FVP_PLATFORM_H_

//
// ACPI table information used to initialize tables.
//
#define EFI_ACPI_ARM_OEM_ID           'L','I','N','A','R','O'   // OEMID 6 bytes long
#define EFI_ACPI_ARM_OEM_TABLE_ID     SIGNATURE_64('R','T','S','M','V','E','V','8') // OEM table id 8 bytes long
#define EFI_ACPI_ARM_OEM_REVISION     0x00000002
#define EFI_ACPI_ARM_CREATOR_ID       SIGNATURE_32('L','N','R','O')
#define EFI_ACPI_ARM_CREATOR_REVISION 0x00000002

// A macro to initialise the common header part of EFI ACPI tables as defined by
// EFI_ACPI_DESCRIPTION_HEADER structure.
#define ARM_ACPI_HEADER(Signature, Type, Revision) {              \
    Signature,                      /* UINT32  Signature */       \
    sizeof (Type),                  /* UINT32  Length */          \
    Revision,                       /* UINT8   Revision */        \
    0,                              /* UINT8   Checksum */        \
    { EFI_ACPI_ARM_OEM_ID },        /* UINT8   OemId[6] */        \
    EFI_ACPI_ARM_OEM_TABLE_ID,      /* UINT64  OemTableId */      \
    EFI_ACPI_ARM_OEM_REVISION,      /* UINT32  OemRevision */     \
    EFI_ACPI_ARM_CREATOR_ID,        /* UINT32  CreatorId */       \
    EFI_ACPI_ARM_CREATOR_REVISION   /* UINT32  CreatorRevision */ \
  }

#endif
