#Copyright (C) 2017 Marvell International Ltd.
#
#Marvell BSD License Option
#
#If you received this File from Marvell, you may opt to use, redistribute and/or
#modify this File under the following licensing terms.
#Redistribution and use in source and binary forms, with or without modification,
#are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#
# * Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
#
# * Neither the name of Marvell nor the names of its contributors may be
# used to endorse or promote products derived from this software without
# specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
#ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
#ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = Armada80x0Db
  PLATFORM_GUID                  = 5cc803a0-9c42-498e-9086-e176d4a1f598
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x0001001A
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64|ARM
  BUILD_TARGETS                  = DEBUG|RELEASE|NOOPT
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Silicon/Marvell/Armada7k8k/Armada7k8k.fdf
  BOARD_DXE_FV_COMPONENTS        = Platform/Marvell/Armada80x0Db/Armada80x0Db.fdf.inc

  #
  # Network definition
  #
  DEFINE NETWORK_IP6_ENABLE             = FALSE
  DEFINE NETWORK_TLS_ENABLE             = FALSE
  DEFINE NETWORK_HTTP_BOOT_ENABLE       = FALSE
  DEFINE NETWORK_ISCSI_ENABLE           = FALSE

!include Silicon/Marvell/Armada7k8k/Armada7k8k.dsc.inc

[Components.common]
  Silicon/Marvell/Armada7k8k/DeviceTree/Armada80x0Db.inf

[Components.AARCH64]
  Silicon/Marvell/Armada7k8k/AcpiTables/Armada80x0Db.inf

[LibraryClasses.common]
  ArmadaBoardDescLib|Platform/Marvell/Armada80x0Db/Armada80x0DbBoardDescLib/Armada80x0DbBoardDescLib.inf
  NonDiscoverableInitLib|Platform/Marvell/Armada80x0Db/NonDiscoverableInitLib/NonDiscoverableInitLib.inf

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################
[PcdsFixedAtBuild.common]
  #MPP
  gMarvellTokenSpaceGuid.PcdMppChipCount|3

  # APN806-A0 MPP SET
  gMarvellTokenSpaceGuid.PcdChip0MppReverseFlag|FALSE
  gMarvellTokenSpaceGuid.PcdChip0MppBaseAddress|0xF06F4000
  gMarvellTokenSpaceGuid.PcdChip0MppPinCount|20
  gMarvellTokenSpaceGuid.PcdChip0MppSel0|{ 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1 }
  gMarvellTokenSpaceGuid.PcdChip0MppSel1|{ 0x1, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3 }

  # CP110 MPP SET - master
  gMarvellTokenSpaceGuid.PcdChip1MppReverseFlag|FALSE
  gMarvellTokenSpaceGuid.PcdChip1MppBaseAddress|0xF2440000
  gMarvellTokenSpaceGuid.PcdChip1MppPinCount|64
  gMarvellTokenSpaceGuid.PcdChip1MppSel0|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip1MppSel1|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip1MppSel2|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip1MppSel3|{ 0xFF, 0xFF, 0x7,  0x0,  0x7,  0xA,  0xA,  0x2,  0x2,  0x5  }
  gMarvellTokenSpaceGuid.PcdChip1MppSel4|{ 0x9,  0x9,  0x8,  0x8,  0x1,  0x1,  0x1,  0x1,  0x1,  0x1  }
  gMarvellTokenSpaceGuid.PcdChip1MppSel5|{ 0x1,  0x1,  0x1,  0x1,  0x1,  0x1,  0xE,  0xE,  0xE,  0xE  }
  gMarvellTokenSpaceGuid.PcdChip1MppSel6|{ 0xE,  0xE,  0xE,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0  }

  # CP110 MPP SET - slave
  gMarvellTokenSpaceGuid.PcdChip2MppReverseFlag|FALSE
  gMarvellTokenSpaceGuid.PcdChip2MppBaseAddress|0xF4440000
  gMarvellTokenSpaceGuid.PcdChip2MppPinCount|64
  gMarvellTokenSpaceGuid.PcdChip2MppSel0|{ 0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3  }
  gMarvellTokenSpaceGuid.PcdChip2MppSel1|{ 0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0x3,  0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip2MppSel2|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x8,  0x9,  0xA  }
  gMarvellTokenSpaceGuid.PcdChip2MppSel3|{ 0xA,  0x8,  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip2MppSel4|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip2MppSel5|{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
  gMarvellTokenSpaceGuid.PcdChip2MppSel6|{ 0xFF, 0xFF, 0xFF, 0x0,  0x0,  0x0,  0x0,  0x0,  0x0,  0x0  }

  # I2C
  gMarvellTokenSpaceGuid.PcdI2cSlaveAddresses|{ 0x50, 0x57, 0x50, 0x57, 0x21, 0x25 }
  gMarvellTokenSpaceGuid.PcdI2cSlaveBuses|{ 0x0, 0x0, 0x1, 0x1, 0x0, 0x0 }
  gMarvellTokenSpaceGuid.PcdI2cControllersEnabled|{ 0x0, 0x1, 0x0, 0x0, 0x1 }
  gMarvellTokenSpaceGuid.PcdEepromI2cAddresses|{ 0x50, 0x57, 0x50, 0x57 }
  gMarvellTokenSpaceGuid.PcdEepromI2cBuses|{ 0x0, 0x0, 0x1, 0x1 }
  gMarvellTokenSpaceGuid.PcdI2cClockFrequency|250000000
  gMarvellTokenSpaceGuid.PcdI2cBaudRate|100000
  gMarvellTokenSpaceGuid.PcdI2cBusCount|2

  #SPI
  gMarvellTokenSpaceGuid.PcdSpiRegBase|0xF4700680
  gMarvellTokenSpaceGuid.PcdSpiMaxFrequency|10000000
  gMarvellTokenSpaceGuid.PcdSpiClockFrequency|200000000

  gMarvellTokenSpaceGuid.PcdSpiFlashMode|3
  gMarvellTokenSpaceGuid.PcdSpiFlashCs|0

  #ComPhy
  gMarvellTokenSpaceGuid.PcdComPhyDevices|{ 0x1, 0x1 }
  # ComPhy0
  # 0: PCIE0         5 Gbps
  # 1: SATA0         5 Gbps
  # 2: SFI           10.31 Gbps
  # 3: SATA1         5 Gbps
  # 4: USB_HOST1     5 Gbps
  # 5: PCIE2         5 Gbps
  gMarvellTokenSpaceGuid.PcdChip0ComPhyTypes|{ $(CP_PCIE0), $(CP_SATA0), $(CP_SFI), $(CP_SATA1), $(CP_USB3_HOST1), $(CP_PCIE2) }
  gMarvellTokenSpaceGuid.PcdChip0ComPhySpeeds|{ $(CP_5G), $(CP_5G), $(CP_10_3125G), $(CP_5G), $(CP_5G), $(CP_5G) }
  # ComPhy1
  # 0: PCIE0         5 Gbps
  # 1: SATA0         5 Gbps
  # 2: SFI           10.31 Gbps
  # 3: SATA1         5 Gbps
  # 4: PCIE1         5 Gbps
  # 5: PCIE2         5 Gbps
  gMarvellTokenSpaceGuid.PcdChip1ComPhyTypes|{ $(CP_PCIE0), $(CP_SATA2), $(CP_SFI), $(CP_SATA3), $(CP_PCIE1), $(CP_PCIE2) }
  gMarvellTokenSpaceGuid.PcdChip1ComPhySpeeds|{ $(CP_5G), $(CP_5G), $(CP_10_3125G), $(CP_5G), $(CP_5G), $(CP_5G) }

  #UtmiPhy
  gMarvellTokenSpaceGuid.PcdUtmiControllersEnabled|{ 0x1, 0x1, 0x1, 0x0 }
  gMarvellTokenSpaceGuid.PcdUtmiPortType|{ $(UTMI_USB_HOST0), $(UTMI_USB_HOST1), $(UTMI_USB_HOST0), $(UTMI_USB_HOST1) }

  #MDIO
  gMarvellTokenSpaceGuid.PcdMdioControllersEnabled|{ 0x1, 0x1 }

  #PHY
  gMarvellTokenSpaceGuid.PcdPhy2MdioController|{ 0x0, 0x1 }
  gMarvellTokenSpaceGuid.PcdPhyDeviceIds|{ 0x0, 0x0 }
  gMarvellTokenSpaceGuid.PcdPhySmiAddresses|{ 0x1, 0x0 }
  gMarvellTokenSpaceGuid.PcdPhyStartupAutoneg|FALSE

  #NET
  gMarvellTokenSpaceGuid.PcdPp2GopIndexes|{ 0x0, 0x3, 0x0, 0x2 }
  gMarvellTokenSpaceGuid.PcdPp2InterfaceAlwaysUp|{ 0x0, 0x0, 0x0, 0x0 }
  gMarvellTokenSpaceGuid.PcdPp2InterfaceSpeed|{ $(PHY_SPEED_10000), $(PHY_SPEED_1000), $(PHY_SPEED_10000), $(PHY_SPEED_1000) }
  gMarvellTokenSpaceGuid.PcdPp2PhyConnectionTypes|{ $(PHY_SFI), $(PHY_RGMII), $(PHY_SFI), $(PHY_RGMII) }
  gMarvellTokenSpaceGuid.PcdPp2PhyIndexes|{ 0xFF, 0x0, 0xFF, 0x1 }
  gMarvellTokenSpaceGuid.PcdPp2Port2Controller|{ 0x0, 0x0, 0x1, 0x1 }
  gMarvellTokenSpaceGuid.PcdPp2PortIds|{ 0x0, 0x2, 0x0, 0x1 }
  gMarvellTokenSpaceGuid.PcdPp2Controllers|{ 0x1, 0x1 }

  #PciEmulation
  gMarvellTokenSpaceGuid.PcdPciEXhci|{ 0x1, 0x1, 0x1, 0x0 }
  gMarvellTokenSpaceGuid.PcdPciEAhci|{ 0x1, 0x1 }
  gMarvellTokenSpaceGuid.PcdPciESdhci|{ 0x1, 0x1 }

  #RTC
  gMarvellTokenSpaceGuid.PcdRtcBaseAddress|0xF4284000
