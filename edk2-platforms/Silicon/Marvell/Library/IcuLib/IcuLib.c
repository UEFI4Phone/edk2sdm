/**
*
*  Copyright (C) 2018, Marvell International Ltd. and its affiliates.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
*  Glossary - abbreviations used in Marvell SampleAtReset library implementation:
*  ICU - Interrupt Consolidation Unit
*  AP - Application Processor hardware block (Armada 7k8k incorporates AP806)
*  CP - South Bridge hardware blocks (Armada 7k8k incorporates CP110)
*
**/

#include "IcuLib.h"

STATIC EFI_EVENT mEfiExitBootServicesEvent;

STATIC CONST ICU_IRQ IrqMapNonSecure[] = {
  {22,   0, IcuIrqTypeLevel}, /* PCIx4 INT A interrupt */
  {23,   1, IcuIrqTypeLevel}, /* PCIx1 INT A interrupt */
  {24,   2, IcuIrqTypeLevel}, /* PCIx1 INT A interrupt */
  {27,   3, IcuIrqTypeLevel}, /* SD/MMC */
  {33,   4, IcuIrqTypeLevel}, /* PPv2 DBG AXI monitor */
  {34,   4, IcuIrqTypeLevel}, /* HB1      AXI monitor */
  {35,   4, IcuIrqTypeLevel}, /* AP       AXI monitor */
  {36,   4, IcuIrqTypeLevel}, /* PPv2     AXI monitor */
  {39,   5, IcuIrqTypeLevel}, /* PPv2 Irq */
  {40,   6, IcuIrqTypeLevel}, /* PPv2 Irq */
  {41,   7, IcuIrqTypeLevel}, /* PPv2 Irq */
  {43,   8, IcuIrqTypeLevel}, /* PPv2 Irq */
  {44,   9, IcuIrqTypeLevel}, /* PPv2 Irq */
  {45,  10, IcuIrqTypeLevel}, /* PPv2 Irq */
  {47,  11, IcuIrqTypeLevel}, /* PPv2 Irq */
  {48,  12, IcuIrqTypeLevel}, /* PPv2 Irq */
  {49,  13, IcuIrqTypeLevel}, /* PPv2 Irq */
  {51,  14, IcuIrqTypeLevel}, /* PPv2 Irq */
  {52,  15, IcuIrqTypeLevel}, /* PPv2 Irq */
  {53,  16, IcuIrqTypeLevel}, /* PPv2 Irq */
  {55,  17, IcuIrqTypeLevel}, /* PPv2 Irq */
  {56,  18, IcuIrqTypeLevel}, /* PPv2 Irq */
  {57,  19, IcuIrqTypeLevel}, /* PPv2 Irq */
  {59,  20, IcuIrqTypeLevel}, /* PPv2 Irq */
  {60,  21, IcuIrqTypeLevel}, /* PPv2 Irq */
  {61,  22, IcuIrqTypeLevel}, /* PPv2 Irq */
  {63,  23, IcuIrqTypeLevel}, /* PPv2 Irq */
  {64,  24, IcuIrqTypeLevel}, /* PPv2 Irq */
  {65,  25, IcuIrqTypeLevel}, /* PPv2 Irq */
  {67,  26, IcuIrqTypeLevel}, /* PPv2 Irq */
  {68,  27, IcuIrqTypeLevel}, /* PPv2 Irq */
  {69,  28, IcuIrqTypeLevel}, /* PPv2 Irq */
  {71,  29, IcuIrqTypeLevel}, /* PPv2 Irq */
  {72,  30, IcuIrqTypeLevel}, /* PPv2 Irq */
  {73,  31, IcuIrqTypeLevel}, /* PPv2 Irq */
  {78,  32, IcuIrqTypeLevel}, /* MG Irq */
  {79,  33, IcuIrqTypeLevel}, /* GPIO 56-63 */
  {80,  34, IcuIrqTypeLevel}, /* GPIO 48-55 */
  {81,  35, IcuIrqTypeLevel}, /* GPIO 40-47 */
  {82,  36, IcuIrqTypeLevel}, /* GPIO 32-39 */
  {83,  37, IcuIrqTypeLevel}, /* GPIO 24-31 */
  {84,  38, IcuIrqTypeLevel}, /* GPIO 16-23 */
  {85,  39, IcuIrqTypeLevel}, /* GPIO  8-15 */
  {86,  40, IcuIrqTypeLevel}, /* GPIO  0-7  */
  {88,  41, IcuIrqTypeLevel}, /* EIP-197 ring-0 */
  {89,  42, IcuIrqTypeLevel}, /* EIP-197 ring-1 */
  {90,  43, IcuIrqTypeLevel}, /* EIP-197 ring-2 */
  {91,  44, IcuIrqTypeLevel}, /* EIP-197 ring-3 */
  {92,  45, IcuIrqTypeLevel}, /* EIP-197 int */
  {95,  46, IcuIrqTypeLevel}, /* EIP-150 Irq */
  {102, 47, IcuIrqTypeLevel}, /* USB3 Device Irq */
  {105, 48, IcuIrqTypeLevel}, /* USB3 Host-1 Irq */
  {106, 49, IcuIrqTypeLevel}, /* USB3 Host-0 Irq */
  {107, 50, IcuIrqTypeLevel}, /* SATA Host-1 Irq */
  {109, 50, IcuIrqTypeLevel}, /* SATA Host-0 Irq */
  {115, 52, IcuIrqTypeLevel}, /* NAND Irq */
  {117, 53, IcuIrqTypeLevel}, /* SPI-1 Irq */
  {118, 54, IcuIrqTypeLevel}, /* SPI-0 Irq */
  {120, 55, IcuIrqTypeLevel}, /* I2C 0 Irq */
  {121, 56, IcuIrqTypeLevel}, /* I2C 1 Irq */
  {122, 57, IcuIrqTypeLevel}, /* UART 0 Irq */
  {123, 58, IcuIrqTypeLevel}, /* UART 1 Irq */
  {124, 59, IcuIrqTypeLevel}, /* UART 2 Irq */
  {125, 60, IcuIrqTypeLevel}, /* UART 3 Irq */
  {127, 61, IcuIrqTypeLevel}, /* GOP-3 Irq */
  {128, 62, IcuIrqTypeLevel}, /* GOP-2 Irq */
  {129, 63, IcuIrqTypeLevel}, /* GOP-0 Irq */
};

/*
 * SEI - System Error Interrupts
 * Note: SPI ID 0-20 are reserved for North-Bridge
 */
STATIC ICU_IRQ IrqMapSei[] = {
  {11,  21, IcuIrqTypeLevel}, /* SEI error CP-2-CP */
  {15,  22, IcuIrqTypeLevel}, /* PIDI-64 SOC */
  {16,  23, IcuIrqTypeLevel}, /* D2D error Irq */
  {17,  24, IcuIrqTypeLevel}, /* D2D Irq */
  {18,  25, IcuIrqTypeLevel}, /* NAND error */
  {19,  26, IcuIrqTypeLevel}, /* PCIx4 error */
  {20,  27, IcuIrqTypeLevel}, /* PCIx1_0 error */
  {21,  28, IcuIrqTypeLevel}, /* PCIx1_1 error */
  {25,  29, IcuIrqTypeLevel}, /* SDIO reg error */
  {75,  30, IcuIrqTypeLevel}, /* IOB error */
  {94,  31, IcuIrqTypeLevel}, /* EIP150 error */
  {97,  32, IcuIrqTypeLevel}, /* XOR-1 system error */
  {99,  33, IcuIrqTypeLevel}, /* XOR-0 system error */
  {108, 34, IcuIrqTypeLevel}, /* SATA-1 error */
  {110, 35, IcuIrqTypeLevel}, /* SATA-0 error */
  {114, 36, IcuIrqTypeLevel}, /* TDM-MC error */
  {116, 37, IcuIrqTypeLevel}, /* DFX server Irq */
  {117, 38, IcuIrqTypeLevel}, /* Device bus error */
  {147, 39, IcuIrqTypeLevel}, /* Audio error */
  {171, 40, IcuIrqTypeLevel}, /* PIDI Sync error */
};

/* REI - RAM Error Interrupts */
STATIC CONST ICU_IRQ IrqMapRei[] = {
  {12,  0, IcuIrqTypeLevel}, /* REI error CP-2-CP */
  {26,  1, IcuIrqTypeLevel}, /* SDIO memory error */
  {87,  2, IcuIrqTypeLevel}, /* EIP-197 ECC error */
  {93,  3, IcuIrqTypeEdge},  /* EIP-150 RAM error */
  {96,  4, IcuIrqTypeLevel}, /* XOR-1 memory Irq */
  {98,  5, IcuIrqTypeLevel}, /* XOR-0 memory Irq */
  {100, 6, IcuIrqTypeEdge},  /* USB3 device tx parity */
  {101, 7, IcuIrqTypeEdge},  /* USB3 device rq parity */
  {103, 8, IcuIrqTypeEdge},  /* USB3H-1 RAM error */
  {104, 9, IcuIrqTypeEdge},  /* USB3H-0 RAM error */
};

STATIC CONST ICU_CONFIG IcuInitialConfig = {
  .NonSecure =  { IrqMapNonSecure, ARRAY_SIZE (IrqMapNonSecure) },
  .Sei =        { IrqMapSei, ARRAY_SIZE (IrqMapSei) },
  .Rei =        { IrqMapRei, ARRAY_SIZE (IrqMapRei) },
};

STATIC
VOID
IcuClearIrq (
  IN UINTN IcuBase,
  IN UINTN Nr
)
{
  MmioWrite32 (IcuBase + ICU_INT_CFG (Nr), 0);
}

STATIC
VOID
IcuSetIrq (
  IN UINTN           IcuBase,
  IN CONST ICU_IRQ  *Irq,
  IN UINTN           SpiBase,
  IN ICU_GROUP       Group
  )
{
  UINT32 IcuInt;

  IcuInt  = (Irq->SpiId + SpiBase) | (1 << ICU_INT_ENABLE_OFFSET);
  IcuInt |= Irq->IrqType << ICU_IS_EDGE_OFFSET;
  IcuInt |= Group << ICU_GROUP_OFFSET;

  MmioWrite32 (IcuBase + ICU_INT_CFG (Irq->IcuId), IcuInt);
}

STATIC
VOID
IcuConfigure (
  IN UINTN             CpIndex,
  IN MV_SOC_ICU_DESC  *IcuDesc,
  IN CONST ICU_CONFIG *Config
  )
{
  UINTN IcuBase, Index, SpiOffset, SpiBase;
  CONST ICU_IRQ *Irq;
  ICU_MSI *Msi;

  /* Get ICU registers base address */
  IcuBase = ICU_REG_BASE (CpIndex);
  /* Get the base of the GIC SPI ID in the MSI message */
  SpiBase = IcuDesc->IcuSpiBase;
  /* Get multiple CP110 instances SPI ID shift */
  SpiOffset = CpIndex * ICU_MAX_IRQS_PER_CP;
  /* Get MSI addresses per interrupt group */
  Msi = IcuDesc->IcuMsi;

  /* Set the address for SET_SPI and CLR_SPI registers in AP */
  for (Index = 0; Index < IcuGroupMax; Index++, Msi++) {
    MmioWrite32 (IcuBase + ICU_SET_SPI_AL (Msi->Group),
      Msi->SetSpiAddr & 0xFFFFFFFF);
    MmioWrite32 (IcuBase + ICU_SET_SPI_AH (Msi->Group), Msi->SetSpiAddr >> 32);
    MmioWrite32 (IcuBase + ICU_CLR_SPI_AL (Msi->Group),
      Msi->ClrSpiAddr & 0xFFFFFFFF);
    MmioWrite32 (IcuBase + ICU_CLR_SPI_AH (Msi->Group), Msi->ClrSpiAddr >> 32);
  }

  /* Mask all ICU interrupts */
  for (Index = 0; Index < MAX_ICU_IRQS; Index++) {
    IcuClearIrq (IcuBase, Index);
  }

  /* Configure the ICU interrupt lines */
  Irq = Config->NonSecure.Map;
  for (Index = 0; Index < Config->NonSecure.Size; Index++, Irq++) {
    IcuSetIrq (IcuBase, Irq, SpiBase + SpiOffset, IcuGroupNsr);
  }

  Irq = Config->Sei.Map;
  for (Index = 0; Index < Config->Sei.Size; Index++, Irq++) {
    IcuSetIrq (IcuBase, Irq, SpiBase, IcuGroupSei);
  }

  Irq = Config->Rei.Map;
  for (Index = 0; Index < Config->Rei.Size; Index++, Irq++) {
    IcuSetIrq (IcuBase, Irq, SpiBase, IcuGroupRei);
  }
}

STATIC
VOID
IcuClearGicSpi (
  IN UINTN             CpIndex,
  IN MV_SOC_ICU_DESC  *IcuDesc
  )
{
  CONST ICU_CONFIG *Config;
  UINTN Index, SpiOffset, SpiBase;
  CONST ICU_IRQ *Irq;
  ICU_MSI *Msi;

  Config = &IcuInitialConfig;

  /* Get the base of the GIC SPI ID in the MSI message */
  SpiBase = IcuDesc->IcuSpiBase;
  /* Get multiple CP110 instances SPI ID shift */
  SpiOffset = CpIndex * ICU_MAX_IRQS_PER_CP;
  /* Get MSI addresses per interrupt group */
  Msi = IcuDesc->IcuMsi;

  /* Clear ICU-generated GIC SPI interrupts */
  Irq = Config->NonSecure.Map;
  for (Index = 0; Index < Config->NonSecure.Size; Index++, Irq++) {
    MmioWrite32 (Msi->ClrSpiAddr, Irq->SpiId + SpiBase + SpiOffset);
  }
}

VOID
EFIAPI
IcuCleanUp (
  IN EFI_EVENT  Event,
  IN VOID      *Context
  )
{
  MV_SOC_ICU_DESC *IcuDesc;
  UINTN CpCount, CpIndex;

  IcuDesc = Context;

  CpCount = FixedPcdGet8 (PcdMaxCpCount);
  if (CpCount > ICU_MAX_SUPPORTED_UNITS) {
    CpCount = ICU_MAX_SUPPORTED_UNITS;
  }

  for (CpIndex = 0; CpIndex < CpCount; CpIndex++) {
    IcuClearGicSpi (CpIndex, IcuDesc);
  }
}

EFI_STATUS
EFIAPI
ArmadaIcuInitialize (
  )
{
  MV_SOC_ICU_DESC *IcuDesc;
  UINTN CpCount, CpIndex;
  EFI_STATUS Status;

  /*
   * Due to limited amount of interrupt lanes, only 2 units can be
   * wired to the GIC.
   */
  CpCount = FixedPcdGet8 (PcdMaxCpCount);
  if (CpCount > ICU_MAX_SUPPORTED_UNITS) {
    DEBUG ((DEBUG_ERROR,
      "%a: Default ICU to GIC mapping is available for maximum %d CP110 units",
      ICU_MAX_SUPPORTED_UNITS,
      __FUNCTION__));
    CpCount = ICU_MAX_SUPPORTED_UNITS;
  }

  /* Obtain SoC description of the ICU */
  Status = ArmadaSoCDescIcuGet (&IcuDesc);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  /* Configure default ICU to GIC interrupt mapping for each CP110 */
  for (CpIndex = 0; CpIndex < CpCount; CpIndex++) {
    IcuConfigure (CpIndex, IcuDesc, &IcuInitialConfig);
  }

  /*
   * In order to be immune to the OS capability of clearing ICU-generated
   * GIC interrupts, register ExitBootServices event, that will
   * make sure they remain disabled during OS boot.
   */
  Status = gBS->CreateEvent (EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  IcuCleanUp,
                  IcuDesc,
                  &mEfiExitBootServicesEvent);

  return Status;
}
