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

#include <Uefi.h>

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/SampleAtResetLib.h>

#include "Armada7k8kSampleAtResetLib.h"

UINT32
EFIAPI
SampleAtResetGetCpuFrequency (
  VOID
  )
{
  CONST PLL_FREQUENCY_DESCRIPTION *PllFrequencies;
  UINT32 ClockValue;
  UINT32 Index;

  ClockValue = MmioAnd32 (AP806_SAR_BASE, SAR_CLOCK_FREQUENCY_MODE_MASK);

  PllFrequencies = PllFrequencyTable;

  for (Index = 0; Index < SAR_MAX_OPTIONS; Index++, PllFrequencies++) {
    if (PllFrequencies->ClockingOption == ClockValue) {
      break;
    }
  }

  return PllFrequencies->CpuFrequency;
}

UINT32
EFIAPI
SampleAtResetGetDramFrequency (
  VOID
  )
{
  CONST PLL_FREQUENCY_DESCRIPTION *PllFrequencies;
  UINT32 ClockValue;
  UINT32 Index;

  ClockValue = MmioAnd32 (AP806_SAR_BASE, SAR_CLOCK_FREQUENCY_MODE_MASK);

  PllFrequencies = PllFrequencyTable;

  for (Index = 0; Index < SAR_MAX_OPTIONS; Index++, PllFrequencies++) {
    if (PllFrequencies->ClockingOption == ClockValue) {
      break;
    }
  }

  return PllFrequencies->DdrFrequency;
}
