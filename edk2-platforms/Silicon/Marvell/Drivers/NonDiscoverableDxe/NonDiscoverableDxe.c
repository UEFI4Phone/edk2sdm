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

#include <PiDxe.h>

#include <Library/DebugLib.h>
#include <Library/NonDiscoverableDeviceRegistrationLib.h>
#include <Library/NonDiscoverableInitLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/BoardDesc.h>
#include <Protocol/EmbeddedExternalDevice.h>

//
// NonDiscoverable devices registration
//
STATIC
EFI_STATUS
NonDiscoverableInitXhci (
  IN MV_BOARD_XHCI_DESC *Desc
  )
{
  EFI_STATUS Status;
  UINT8 i;

  for (i = 0; i < Desc->XhciDevCount; i++) {
    Status = RegisterNonDiscoverableMmioDevice (
                     NonDiscoverableDeviceTypeXhci,
                     Desc[i].SoC->XhciDmaType,
                     NonDiscoverableDeviceInitializerGet (
                       NonDiscoverableDeviceTypeXhci,
                       i),
                     NULL,
                     1,
                     Desc[i].SoC->XhciBaseAddress,
                     Desc[i].SoC->XhciMemSize
                   );

    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "NonDiscoverable: Cannot install Xhci device %d\n", i));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
NonDiscoverableInitAhci (
  IN MV_BOARD_AHCI_DESC *Desc
  )
{
  EFI_STATUS Status;
  UINT8 i;

  for (i = 0; i < Desc->AhciDevCount; i++) {
    Status = RegisterNonDiscoverableMmioDevice (
                     NonDiscoverableDeviceTypeAhci,
                     Desc[i].SoC->AhciDmaType,
                     NonDiscoverableDeviceInitializerGet (
                       NonDiscoverableDeviceTypeAhci,
                       i),
                     NULL,
                     1,
                     Desc[i].SoC->AhciBaseAddress,
                     Desc[i].SoC->AhciMemSize
                   );

    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "NonDiscoverable: Cannot install Ahci device %d\n", i));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
NonDiscoverableInitSdhci (
  IN MV_BOARD_SDMMC_DESC *Desc
  )
{
  EFI_STATUS Status;
  UINT8 i;

  for (i = 0; i < Desc->SdMmcDevCount; i++) {
    Status = RegisterNonDiscoverableMmioDevice (
                     NonDiscoverableDeviceTypeSdhci,
                     Desc[i].SoC->SdMmcDmaType,
                     NonDiscoverableDeviceInitializerGet (
                       NonDiscoverableDeviceTypeSdhci,
                       i),
                     NULL,
                     1,
                     Desc[i].SoC->SdMmcBaseAddress,
                     Desc[i].SoC->SdMmcMemSize
                   );

    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_ERROR, "NonDiscoverable: Cannot install Sdhci device %d\n", i));
      return Status;
    }
  }

  return EFI_SUCCESS;
}

//
// Entry point
//
EFI_STATUS
EFIAPI
NonDiscoverableEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  MARVELL_BOARD_DESC_PROTOCOL *BoardDescProtocol;
  MV_BOARD_SDMMC_DESC *SdMmcBoardDesc;
  MV_BOARD_AHCI_DESC *AhciBoardDesc;
  MV_BOARD_XHCI_DESC *XhciBoardDesc;
  EFI_STATUS Status;

  /* Obtain list of available controllers */
  Status = gBS->LocateProtocol (&gMarvellBoardDescProtocolGuid,
                  NULL,
                  (VOID **)&BoardDescProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  /* Xhci */
  Status = BoardDescProtocol->BoardDescXhciGet (BoardDescProtocol,
                                &XhciBoardDesc);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = NonDiscoverableInitXhci (XhciBoardDesc);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  BoardDescProtocol->BoardDescFree (XhciBoardDesc);

  /* Ahci */
  Status = BoardDescProtocol->BoardDescAhciGet (BoardDescProtocol,
                                &AhciBoardDesc);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = NonDiscoverableInitAhci (AhciBoardDesc);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  BoardDescProtocol->BoardDescFree (AhciBoardDesc);

  /* SdMmc */
  Status = BoardDescProtocol->BoardDescSdMmcGet (BoardDescProtocol,
                                &SdMmcBoardDesc);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = NonDiscoverableInitSdhci (SdMmcBoardDesc);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EFI_SUCCESS;
}
