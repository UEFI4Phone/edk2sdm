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

#ifndef __MV_EEPROM_H__
#define __MV_EEPROM_H__

#include <Uefi.h>

#define EEPROM_SIGNATURE          SIGNATURE_32 ('E', 'E', 'P', 'R')

#define MAX_BUFFER_LENGTH 64

#define I2C_GUID \
  { \
  0xadc1901b, 0xb83c, 0x4831, { 0x8f, 0x59, 0x70, 0x89, 0x8f, 0x26, 0x57, 0x1e } \
  }

typedef struct {
  UINT32  Signature;
  EFI_HANDLE ControllerHandle;
  EFI_I2C_IO_PROTOCOL *I2cIo;
  MARVELL_EEPROM_PROTOCOL EepromProtocol;
} EEPROM_CONTEXT;

#define EEPROM_SC_FROM_IO(a) CR (a, EEPROM_CONTEXT, I2cIo, EEPROM_SIGNATURE)
#define EEPROM_SC_FROM_EEPROM(a) CR (a, EEPROM_CONTEXT, EepromProtocol, EEPROM_SIGNATURE)

EFI_STATUS
EFIAPI
MvEepromSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL            *This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
MvEepromStart (
  IN EFI_DRIVER_BINDING_PROTOCOL            *This,
  IN EFI_HANDLE                             ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL               *RemainingDevicePath OPTIONAL
  );

EFI_STATUS
EFIAPI
MvEepromStop (
  IN EFI_DRIVER_BINDING_PROTOCOL            *This,
  IN  EFI_HANDLE                            ControllerHandle,
  IN  UINTN                                 NumberOfChildren,
  IN  EFI_HANDLE                            *ChildHandleBuffer OPTIONAL
  );

EFI_STATUS
EFIAPI
MvEepromTransfer (
  IN CONST MARVELL_EEPROM_PROTOCOL *This,
  IN UINT16 Address,
  IN UINT32 Length,
  IN UINT8 *Buffer,
  IN UINT8 Operation
  );
#endif // __MV_EEPROM_H__
