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

#ifndef __MDIO_H__
#define __MDIO_H__

#define MARVELL_MDIO_PROTOCOL_GUID { 0x40010b03, 0x5f08, 0x496a, { 0xa2, 0x64, 0x10, 0x5e, 0x72, 0xd3, 0x71, 0xaa }}

typedef struct _MARVELL_MDIO_PROTOCOL MARVELL_MDIO_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *MARVELL_MDIO_READ) (
  IN CONST MARVELL_MDIO_PROTOCOL *This,
  IN UINT32 PhyAddr,
  IN UINT32 MdioIndex,
  IN UINT32 RegOff,
  IN UINT32 *Data
  );

typedef
EFI_STATUS
(EFIAPI *MARVELL_MDIO_WRITE) (
  IN CONST MARVELL_MDIO_PROTOCOL *This,
  IN UINT32 PhyAddr,
  IN UINT32 MdioIndex,
  IN UINT32 RegOff,
  IN UINT32 Data
  );

struct _MARVELL_MDIO_PROTOCOL {
  MARVELL_MDIO_READ Read;
  MARVELL_MDIO_WRITE Write;
  UINTN *BaseAddresses;
  UINTN ControllerCount;
};

extern EFI_GUID gMarvellMdioProtocolGuid;
#endif
