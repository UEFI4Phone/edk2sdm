/*******************************************************************************
Copyright (C) 2017 Marvell International Ltd.

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

#define CCU_MC_RCR_REG                  0xf0001700
#define REMAP_EN_MASK                   0x1
#define REMAP_SIZE_OFFS                 20
#define REMAP_SIZE_MASK                 (0xfff << REMAP_SIZE_OFFS)
#define CCU_MC_RTBR_REG                 0xf0001708
#define TARGET_BASE_OFFS                10
#define TARGET_BASE_MASK                (0xfffff << TARGET_BASE_OFFS)

#define DRAM_REMAP_ENABLED \
          (MmioRead32 (CCU_MC_RCR_REG) & REMAP_EN_MASK)
#define DRAM_REMAP_SIZE \
          (MmioRead32 (CCU_MC_RCR_REG) & REMAP_SIZE_MASK) + SIZE_1MB
#define DRAM_REMAP_TARGET \
          (MmioRead32 (CCU_MC_RTBR_REG) << TARGET_BASE_OFFS)
