/** @file
*
*  Copyright (c) 2018, ARM Limited. All rights reserved.
*
*  SPDX-License-Identifier: BSD-2-Clause-Patent
*
**/

#ifndef __SGI_PLATFORM_H__
#define __SGI_PLATFORM_H__

/***********************************************************************************
// Platform Memory Map
************************************************************************************/

// Expansion AXI - SMC Chip Select 0
#define SGI_EXP_SMC_CS0_BASE                      0x08000000
#define SGI_EXP_SMC_CS0_SZ                        SIZE_64MB

// Expansion AXI - SMC Chip Select 1
#define SGI_EXP_SMC_CS1_BASE                      0x0C000000
#define SGI_EXP_SMC_CS1_SZ                        SIZE_64MB

// Expansion AXI - SMSC 91C111 (Ethernet)
#define SGI_EXP_SMSC91X_BASE                      0x18000000
#define SGI_EXP_SMSC91X_SZ                        SIZE_64MB

// Expansion AXI - System peripherals
#define SGI_EXP_SYS_PERIPH_BASE                   0x1C000000
#define SGI_EXP_SYS_PERIPH_SZ                     SIZE_2MB

// Base address of system peripherals
#define SGI_EXP_SYSPH_SYSTEM_REGISTERS            0x1C010000
#define SGI_EXP_SYSPH_VIRTIO_BLOCK_BASE           0x1C130000

// Sub System Peripherals - UART0
#define SGI_SUBSYS_UART0_BASE                     0x2A400000
#define SGI_SUBSYS_UART0_SZ                       0x00010000

// Sub System Peripherals - UART1
#define SGI_SUBSYS_UART1_BASE                     0x2A410000
#define SGI_SUBSYS_UART1_SZ                       0x00010000

// Sub System Peripherals - Generic Watchdog
#define SGI_SUBSYS_GENERIC_WDOG_BASE              0x2A440000
#define SGI_SUBSYS_GENERIC_WDOG_SZ                SIZE_128KB

// Sub System Peripherals - GIC
#define SGI_SUBSYS_GENERIC_GIC_BASE               0x30000000
#define SGI_SUBSYS_GENERIC_GICR_BASE              0x300C0000
#define SGI_SUBSYS_GENERIC_GIC_SZ                 SIZE_1MB

// Expansion AXI - Platform Peripherals - HDLCD1
#define SGI_EXP_PLAT_PERIPH_HDLCD1_BASE           0x7FF60000
#define SGI_EXP_PLAT_PERIPH_HDLCD1_SZ             SIZE_64KB

// Expansion AXI - Platform Peripherals - UART0
#define SGI_EXP_PLAT_PERIPH_UART0_BASE            0x7FF70000
#define SGI_EXP_PLAT_PERIPH_UART0_SZ              SIZE_64KB

// Expansion AXI - Platform Peripherals - UART1
#define SGI_EXP_PLAT_PERIPH_UART1_BASE            0x7FF80000
#define SGI_EXP_PLAT_PERIPH_UART1_SZ              SIZE_64KB

// Register offsets into the System Registers Block
#define SGI_SYSPH_SYS_REG_FLASH                   0x4C
#define SGI_SYSPH_SYS_REG_FLASH_RWEN              0x1

// SGI575_VERSION values
#define SGI575_CONF_NUM                           0x3
#define SGI575_PART_NUM                           0x783

//RDN1E1EDGE Platform Identification values
#define RD_N1E1_EDGE_PART_NUM                     0x786
#define RD_N1_EDGE_CONF_ID                        0x1
#define RD_E1_EDGE_CONF_ID                        0x2

#define SGI_CONFIG_MASK                           0x0F
#define SGI_CONFIG_SHIFT                          0x1C
#define SGI_PART_NUM_MASK                         0xFFF

// ARM platform description data.
typedef struct {
  UINTN  PlatformId;
  UINTN  ConfigId;
} SGI_PLATFORM_DESCRIPTOR;

#endif // __SGI_PLATFORM_H__
