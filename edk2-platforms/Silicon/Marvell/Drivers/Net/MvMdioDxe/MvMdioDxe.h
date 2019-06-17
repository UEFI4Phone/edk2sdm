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

#ifndef __MDIO_DXE_H__
#define __MDIO_DXE_H__

#include <Uefi.h>

#define MVEBU_SMI_TIMEOUT      10000

/* SMI register fields */
#define  MVEBU_SMI_DATA_OFFS      0  /* Data */
#define  MVEBU_SMI_DATA_MASK      (0xffff << MVEBU_SMI_DATA_OFFS)
#define  MVEBU_SMI_DEV_ADDR_OFFS      16  /* PHY device address */
#define  MVEBU_SMI_REG_ADDR_OFFS      21  /* PHY device reg addr*/
#define  MVEBU_SMI_OPCODE_OFFS      26  /* Write/Read opcode */
#define  MVEBU_SMI_OPCODE_READ      (1 << MVEBU_SMI_OPCODE_OFFS)
#define  MVEBU_SMI_READ_VALID      (1 << 27)  /* Read Valid */
#define  MVEBU_SMI_BUSY        (1 << 28)  /* Busy */

#define  MVEBU_PHY_REG_MASK      0x1f
#define  MVEBU_PHY_ADDR_MASK      0x1f

#define MdioRegWrite32(x, y) MmioWrite32((y), (x))

#endif // __MDIO_DXE_H__
