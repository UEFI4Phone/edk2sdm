/** @file
 *
 *  GPIO manipulation.
 *
 *  Copyright (c) 2018, Andrei Warkentin <andrey.warkentin@gmail.com>
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#ifndef __GPIO_LIB__
#define __GPIO_LIB__

#include <IndustryStandard/Bcm2836Gpio.h>

VOID
GpioPinFuncSet (
  IN  UINTN Pin,
  IN  UINTN Function
  );

UINTN
GpioPinFuncGet (
  IN  UINTN Pin
  );

#endif /* __GPIO_LIB__ */
