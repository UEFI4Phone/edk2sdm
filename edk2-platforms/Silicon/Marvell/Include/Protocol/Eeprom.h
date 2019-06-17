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

#ifndef __MARVELL_EEPROM_H__
#define __MARVELL_EEPROM_H__

#define MARVELL_EEPROM_PROTOCOL_GUID { 0x71954bda, 0x60d3, 0x4ef8, { 0x8e, 0x3c, 0x0e, 0x33, 0x9f, 0x3b, 0xc2, 0x2b }}

typedef struct _MARVELL_EEPROM_PROTOCOL MARVELL_EEPROM_PROTOCOL;

#define EEPROM_READ   0x1
#define EEPROM_WRITE  0x0
typedef
EFI_STATUS
(EFIAPI *EFI_EEPROM_TRANSFER) (
  IN CONST MARVELL_EEPROM_PROTOCOL *This,
  IN UINT16 Address,
  IN UINT32 Length,
  IN UINT8 *Buffer,
  IN UINT8 Operation
  );

struct _MARVELL_EEPROM_PROTOCOL {
  EFI_EEPROM_TRANSFER Transfer;
  UINT32 Identifier;
};

extern EFI_GUID gMarvellEepromProtocolGuid;
#endif
