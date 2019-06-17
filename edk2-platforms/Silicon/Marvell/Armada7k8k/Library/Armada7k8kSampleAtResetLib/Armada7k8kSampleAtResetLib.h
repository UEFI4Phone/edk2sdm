/********************************************************************************
Copyright (C) 2018 Marvell International Ltd.

Marvell BSD License Option

If you received this File from Marvell, you may opt to use, redistribute and/or
modify this File under the following licensing terms.
Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must Retain the above copyright notice,
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

Glossary - abbreviations used in Marvell SampleAtReset library implementation:
AP - Application Processor hardware block (Armada 7k8k incorporates AP806)
CP - South Bridge hardware blocks (Armada 7k8k incorporates CP110)
SAR - Sample At Reset

*******************************************************************************/

#define SAR_MAX_OPTIONS           16

#define AP806_SAR_BASE            0xf06f8200
#define SAR_CLOCK_FREQUENCY_MODE_MASK  0x1f

#define CP110_SAR_BASE(_CpIndex)  (0xf2000000 + (0x2000000 * (_CpIndex)) + 0x400200)

typedef enum {
  CPU_2000_DDR_1200_RCLK_1200 = 0x0,
  CPU_2000_DDR_1050_RCLK_1050 = 0x1,
  CPU_1600_DDR_800_RCLK_800   = 0x4,
  CPU_1800_DDR_1200_RCLK_1200 = 0x6,
  CPU_1800_DDR_1050_RCLK_1050 = 0x7,
  CPU_1600_DDR_1050_RCLK_1050 = 0x0d,
  CPU_1000_DDR_650_RCLK_650   = 0x13,
  CPU_1300_DDR_800_RCLK_800   = 0x14,
  CPU_1300_DDR_650_RCLK_650   = 0x17,
  CPU_1200_DDR_800_RCLK_800   = 0x19,
  CPU_1400_DDR_800_RCLK_800   = 0x1a,
  CPU_600_DDR_800_RCLK_800    = 0x1b,
  CPU_800_DDR_800_RCLK_800    = 0x1c,
  CPU_1000_DDR_800_RCLK_800   = 0x1d,
} CLOCKING_OPTIONS;

typedef struct {
  UINT32 CpuFrequency;
  UINT32 DdrFrequency;
  UINT32 RingFrequency;
  CLOCKING_OPTIONS ClockingOption;
} PLL_FREQUENCY_DESCRIPTION;

STATIC CONST PLL_FREQUENCY_DESCRIPTION PllFrequencyTable[SAR_MAX_OPTIONS] = {
  /* CPU   DDR   Ring  [MHz] */
  {2000,  1200,  1200, CPU_2000_DDR_1200_RCLK_1200},
  {2000,  1050,  1050, CPU_2000_DDR_1050_RCLK_1050},
  {1800,  1200,  1200, CPU_1800_DDR_1200_RCLK_1200},
  {1800,  1050,  1050, CPU_1800_DDR_1050_RCLK_1050},
  {1600,  1050,  1050, CPU_1600_DDR_1050_RCLK_1050},
  {1300,  800 ,  800 , CPU_1300_DDR_800_RCLK_800},
  {1300,  650 ,  650 , CPU_1300_DDR_650_RCLK_650},
  {1600,  800 ,  800 , CPU_1600_DDR_800_RCLK_800},
  {1000,  650 ,  650 , CPU_1000_DDR_650_RCLK_650},
  {1200,  800 ,  800 , CPU_1200_DDR_800_RCLK_800},
  {1400,  800 ,  800 , CPU_1400_DDR_800_RCLK_800},
  {600 ,  800 ,  800 , CPU_600_DDR_800_RCLK_800},
  {800 ,  800 ,  800 , CPU_800_DDR_800_RCLK_800},
  {1000,  800 ,  800 , CPU_1000_DDR_800_RCLK_800}
};
