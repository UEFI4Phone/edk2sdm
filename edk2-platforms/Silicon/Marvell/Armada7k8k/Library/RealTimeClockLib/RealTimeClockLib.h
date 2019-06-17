/********************************************************************************
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

#ifndef __RTCLIB_H__
#define __RTCLIB_H__

/* Armada 70x0 SoC registers */
#define RTC_STATUS_REG                          0x0
#define RTC_TIME_REG                            0xC
#define RTC_IRQ_2_CONFIG_REG                    0x8
#define RTC_IRQ_ALARM_EN                        0x1
#define RTC_ALARM_2_REG                         0x14
#define RTC_BRIDGE_TIMING_CTRL0_REG_OFFS        0x80
#define RTC_BRIDGE_TIMING_CTRL1_REG_OFFS        0x84
#define RTC_IRQ_STATUS_REG                      0x90
#define RTC_IRQ_ALARM_MASK                      0x1
#define RTC_WRITE_PERIOD_DELAY_MASK             0xFFFF
#define RTC_WRITE_PERIOD_DELAY_DEFAULT          0x3FF
#define RTC_WRITE_SETUP_DELAY_MASK              (0xFFFF << 16)
#define RTC_WRITE_SETUP_DELAY_DEFAULT           (0x29 << 16)
#define RTC_READ_OUTPUT_DELAY_MASK              0xFFFF
#define RTC_READ_OUTPUT_DELAY_DEFAULT           0x3F

#endif /* __RTCLIB_H__ */
