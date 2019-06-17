/** @file
 *
 *  Copyright (c) 2018, Andrei Warkentin <andrey.warkentin@gmail.com>
 *  Copyright (c) Microsoft Corporation. All rights reserved.
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#ifndef __BCM2836_GPIO_H__
#define __BCM2836_GPIO_H__

#define GPIO_BASE_ADDRESS  (BCM2836_SOC_REGISTERS + 0x00200000)

#define GPIO_GPFSEL0       (GPIO_BASE_ADDRESS + 0x00)
#define GPIO_GPFSEL1       (GPIO_BASE_ADDRESS + 0x04)
#define GPIO_GPFSEL2       (GPIO_BASE_ADDRESS + 0x08)
#define GPIO_GPFSEL3       (GPIO_BASE_ADDRESS + 0x0C)
#define GPIO_GPFSEL4       (GPIO_BASE_ADDRESS + 0x10)
#define GPIO_GPFSEL5       (GPIO_BASE_ADDRESS + 0x14)

#define GPIO_GPCLR0        (GPIO_BASE_ADDRESS + 0x28)
#define GPIO_GPCLR1        (GPIO_BASE_ADDRESS + 0x2C)

#define GPIO_GPSET0        (GPIO_BASE_ADDRESS + 0x1C)
#define GPIO_GPSET1        (GPIO_BASE_ADDRESS + 0x20)

#define GPIO_FSEL_INPUT    0x0
#define GPIO_FSEL_OUTPUT   0x1
#define GPIO_FSEL_ALT0     0x4
#define GPIO_FSEL_ALT1     0x5
#define GPIO_FSEL_ALT2     0x6
#define GPIO_FSEL_ALT3     0x7
#define GPIO_FSEL_ALT4     0x3
#define GPIO_FSEL_ALT5     0x2

#define GPIO_FSEL_PINS_PER_REGISTER 10
#define GPIO_FSEL_BITS_PER_PIN      3
#define GPIO_FSEL_MASK              ((1 << GPIO_FSEL_BITS_PER_PIN) - 1)

#define GPIO_PINS          54

#endif /* __BCM2836_GPIO_H__ */
