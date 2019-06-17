/** @file
 *
 *  GPIO manipulation.
 *
 *  Copyright (c) 2018, Andrei Warkentin <andrey.warkentin@gmail.com>
 *
 *  SPDX-License-Identifier: BSD-2-Clause-Patent
 *
 **/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/GpioLib.h>
#include <IndustryStandard/Bcm2836.h>
#include <IndustryStandard/Bcm2836Gpio.h>

STATIC
VOID
GpioFSELModify (
  IN  UINTN RegIndex,
  IN  UINT32 ModifyMask,
  IN  UINT32 FunctionMask
  )
{
  UINT32 Val;
  EFI_PHYSICAL_ADDRESS Reg;

  Reg = RegIndex * sizeof (UINT32) + GPIO_GPFSEL0;

  ASSERT (Reg <= GPIO_GPFSEL5);
  ASSERT ((~ModifyMask & FunctionMask) == 0);

  Val = MmioRead32 (Reg);
  Val &= ~ModifyMask;
  Val |= FunctionMask;
  MmioWrite32 (Reg, Val);
}

VOID
GpioPinFuncSet (
  IN  UINTN Pin,
  IN  UINTN Function
  )
{
  UINTN RegIndex;
  UINTN SelIndex;
  UINT32 ModifyMask;
  UINT32 FunctionMask;

  ASSERT (Pin < GPIO_PINS);
  ASSERT (Function <= GPIO_FSEL_MASK);

  RegIndex = Pin / 10;
  SelIndex = Pin % 10;

  ModifyMask = GPIO_FSEL_MASK << (SelIndex * GPIO_FSEL_BITS_PER_PIN);
  FunctionMask = Function << (SelIndex * GPIO_FSEL_BITS_PER_PIN);
  GpioFSELModify (RegIndex, ModifyMask, FunctionMask);
}

UINTN
GpioPinFuncGet (
  IN  UINTN Pin
  )
{
  UINT32 Val;
  UINTN RegIndex;
  UINTN SelIndex;
  EFI_PHYSICAL_ADDRESS Reg;

  ASSERT (Pin < GPIO_PINS);

  RegIndex = Pin / 10;
  SelIndex = Pin % 10;
  Reg = RegIndex * sizeof (UINT32) + GPIO_GPFSEL0;

  Val = MmioRead32 (Reg);
  Val >>= SelIndex * GPIO_FSEL_BITS_PER_PIN;
  Val &= GPIO_FSEL_MASK;
  return Val;
}
