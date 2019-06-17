/********************************************************************************
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

#include <Protocol/BoardDesc.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/Mdio.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

#include "MvMdioDxe.h"

STATIC
EFI_STATUS
MdioCheckParam (
 INTN PhyAddr,
 INTN RegOff
 )
{
  if (PhyAddr > MVEBU_PHY_ADDR_MASK) {
    DEBUG((DEBUG_ERROR, "Invalid PHY address %d\n", PhyAddr));
    return EFI_INVALID_PARAMETER;
  }

  if (RegOff > MVEBU_PHY_REG_MASK) {
    DEBUG((DEBUG_ERROR, "Invalid register offset %d\n", RegOff));
    return EFI_INVALID_PARAMETER;
  }
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
MdioWaitReady (
  UINTN MdioBase
  )
{
  UINT32 Timeout = MVEBU_SMI_TIMEOUT;
  UINT32 MdioReg;

  /* wait till the SMI is not busy */
  do {
    /* read smi register */
    MdioReg = MmioRead32(MdioBase);
    if (Timeout-- == 0) {
      DEBUG((DEBUG_ERROR, "SMI busy Timeout\n"));
      return EFI_TIMEOUT;
    }
  } while (MdioReg & MVEBU_SMI_BUSY);

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
MdioWaitValid (
  UINTN MdioBase
  )
{
  UINT32 Timeout = MVEBU_SMI_TIMEOUT;
  UINT32 MdioReg;

  /* wait till read value is ready */
  do {
    /* read smi register */
    MdioReg = MmioRead32 (MdioBase);
    if (Timeout-- == 0) {
      DEBUG((DEBUG_ERROR, "SMI read ready time-out\n"));
      return EFI_TIMEOUT;
    }
  } while (!(MdioReg & MVEBU_SMI_READ_VALID));

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
MdioOperation (
  IN CONST MARVELL_MDIO_PROTOCOL *This,
  IN UINT32 PhyAddr,
  IN UINT32 MdioIndex,
  IN UINT32 RegOff,
  IN BOOLEAN Write,
  IN OUT UINT32 *Data
  )
{
  UINTN MdioBase = This->BaseAddresses[MdioIndex];
  UINT32 MdioReg;
  EFI_STATUS Status;

  Status = MdioCheckParam (PhyAddr, RegOff);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MdioDxe: wrong parameters\n"));
    return Status;
  }

  /* wait till the SMI is not busy */
  Status = MdioWaitReady (MdioBase);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MdioDxe: MdioWaitReady error\n"));
    return Status;
  }

  /* fill the phy addr and reg offset and write opcode and data */
  MdioReg = (PhyAddr << MVEBU_SMI_DEV_ADDR_OFFS)
      | (RegOff << MVEBU_SMI_REG_ADDR_OFFS);
  if (Write) {
    MdioReg &= ~MVEBU_SMI_OPCODE_READ;
    MdioReg |= (*Data << MVEBU_SMI_DATA_OFFS);
  } else {
    MdioReg |= MVEBU_SMI_OPCODE_READ;
  }

  /* write the smi register */
  MdioRegWrite32 (MdioReg, MdioBase);

  /* make sure that the write transaction  is over */
  Status = Write ? MdioWaitReady (MdioBase) : MdioWaitValid (MdioBase);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "MdioDxe: MdioWaitReady error\n"));
    return Status;
  }

  if (!Write) {
    *Data = MmioRead32 (MdioBase) & MVEBU_SMI_DATA_MASK;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
MvMdioRead (
  IN CONST MARVELL_MDIO_PROTOCOL *This,
  IN UINT32 PhyAddr,
  IN UINT32 MdioIndex,
  IN UINT32 RegOff,
  IN UINT32 *Data
  )
{
  EFI_STATUS Status;

  Status = MdioOperation (
            This,
            PhyAddr,
            MdioIndex,
            RegOff,
            FALSE,
            Data
            );

  return Status;
}

EFI_STATUS
MvMdioWrite (
  IN CONST MARVELL_MDIO_PROTOCOL *This,
  IN UINT32 PhyAddr,
  IN UINT32 MdioIndex,
  IN UINT32 RegOff,
  IN UINT32 Data
  )
{
  return MdioOperation (
            This,
            PhyAddr,
            MdioIndex,
            RegOff,
            TRUE,
            &Data
            );
}

EFI_STATUS
EFIAPI
MvMdioDxeInitialise (
  IN EFI_HANDLE  ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  MARVELL_BOARD_DESC_PROTOCOL *BoardDescProtocol;
  MV_BOARD_MDIO_DESC *MdioBoardDesc;
  UINT8 Index;
  MARVELL_MDIO_PROTOCOL *Mdio;
  EFI_STATUS Status;
  EFI_HANDLE Handle = NULL;

  /* Obtain list of available controllers */
  Status = gBS->LocateProtocol (&gMarvellBoardDescProtocolGuid,
                  NULL,
                  (VOID **)&BoardDescProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = BoardDescProtocol->BoardDescMdioGet (BoardDescProtocol,
                                &MdioBoardDesc);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Mdio = AllocateZeroPool (sizeof (MARVELL_MDIO_PROTOCOL));
  if (Mdio == NULL) {
    DEBUG ((DEBUG_ERROR, "MdioDxe: Protocol allocation failed\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  Mdio->BaseAddresses = AllocateZeroPool (MdioBoardDesc->MdioDevCount *
                                          sizeof (UINTN));
  if (Mdio->BaseAddresses == NULL) {
    DEBUG ((DEBUG_ERROR, "MdioDxe: Protocol allocation failed\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  /* Obtain base addresses of all possible controllers */
  for (Index = 0; Index < MdioBoardDesc->MdioDevCount; Index++) {
    Mdio->BaseAddresses[Index] = MdioBoardDesc[Index].SoC->MdioBaseAddress;
  }

  Mdio->ControllerCount = MdioBoardDesc->MdioDevCount;
  Mdio->Read = MvMdioRead;
  Mdio->Write = MvMdioWrite;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gMarvellMdioProtocolGuid, Mdio,
                  NULL
                  );

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "Failed to install interfaces\n"));
    return Status;
  }

  BoardDescProtocol->BoardDescFree (MdioBoardDesc);

  return EFI_SUCCESS;
}
