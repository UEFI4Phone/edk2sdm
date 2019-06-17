#
#  Copyright (c) 2018, ARM Limited. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = ArmSgi
  PLATFORM_GUID                  = 3a6b2eae-0275-4b6e-a5d1-bd2ba1ce1fae
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x0001001B
  OUTPUT_DIRECTORY               = Build/$(PLATFORM_NAME)
  SUPPORTED_ARCHITECTURES        = AARCH64|ARM
  BUILD_TARGETS                  = NOOPT|DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = Platform/ARM/SgiPkg/SgiPlatform.fdf
  BUILD_NUMBER                   = 1

!include Platform/ARM/VExpressPkg/ArmVExpress.dsc.inc

[LibraryClasses.common]
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  ArmMmuLib|ArmPkg/Library/ArmMmuLib/ArmMmuBaseLib.inf
  ArmSmcLib|ArmPkg/Library/ArmSmcLib/ArmSmcLib.inf
  ArmPlatformSysConfigLib|Platform/ARM/VExpressPkg/Library/ArmVExpressSysConfigLib/ArmVExpressSysConfigLib.inf
  ArmPlatformLib|Platform/ARM/SgiPkg/Library/PlatformLib/PlatformLib.inf
  BasePathLib|ShellPkg/Library/UefiShellLib/UefiShellLib.inf
  EfiResetSystemLib|ArmPkg/Library/ArmPsciResetSystemLib/ArmPsciResetSystemLib.inf
  LcdHwLib|ArmPlatformPkg/Library/HdLcd/HdLcd.inf
  LcdPlatformLib|Platform/ARM/SgiPkg/Library/HdLcdArmSgiLib/HdLcdArmSgiLib.inf
  NorFlashPlatformLib|Platform/ARM/SgiPkg/Library/NorFlashLib/NorFlashLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf

  # Virtio Support
  VirtioLib|OvmfPkg/Library/VirtioLib/VirtioLib.inf
  VirtioMmioDeviceLib|OvmfPkg/Library/VirtioMmioDeviceLib/VirtioMmioDeviceLib.inf
  FileExplorerLib|MdeModulePkg/Library/FileExplorerLib/FileExplorerLib.inf
  OrderedCollectionLib|MdePkg/Library/BaseOrderedCollectionRedBlackTreeLib/BaseOrderedCollectionRedBlackTreeLib.inf

[LibraryClasses.common.SEC]
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  PeiServicesTablePointerLib|ArmPkg/Library/PeiServicesTablePointerLib/PeiServicesTablePointerLib.inf

[LibraryClasses.common.PEI_CORE, LibraryClasses.common.PEIM]
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  HobLib|MdePkg/Library/PeiHobLib/PeiHobLib.inf
  MemoryAllocationLib|MdePkg/Library/PeiMemoryAllocationLib/PeiMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/PeiPcdLib/PeiPcdLib.inf
  PeiServicesLib|MdePkg/Library/PeiServicesLib/PeiServicesLib.inf
  PeiServicesTablePointerLib|ArmPkg/Library/PeiServicesTablePointerLib/PeiServicesTablePointerLib.inf
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf

[LibraryClasses.common.PEI_CORE]
  PeiCoreEntryPoint|MdePkg/Library/PeiCoreEntryPoint/PeiCoreEntryPoint.inf

[LibraryClasses.common.PEIM]
  PeimEntryPoint|MdePkg/Library/PeimEntryPoint/PeimEntryPoint.inf

[LibraryClasses.common.DXE_CORE]
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.common.DXE_DRIVER]
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf
  PciHostBridgeLib|Platform/ARM/SgiPkg/Library/PciHostBridgeLib/PciHostBridgeLib.inf
  PciSegmentLib|MdePkg/Library/BasePciSegmentLibPci/BasePciSegmentLibPci.inf
  PciLib|MdePkg/Library/BasePciLibPciExpress/BasePciLibPciExpress.inf
  PciExpressLib|MdePkg/Library/BasePciExpressLib/BasePciExpressLib.inf

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
!if $(TARGET) != RELEASE
  DebugLib|MdePkg/Library/DxeRuntimeDebugLibSerialPort/DxeRuntimeDebugLibSerialPort.inf
!endif

[LibraryClasses.common.UEFI_DRIVER, LibraryClasses.common.UEFI_APPLICATION, LibraryClasses.common.DXE_RUNTIME_DRIVER, LibraryClasses.common.DXE_DRIVER]
  PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
  gArmSgiTokenSpaceGuid.PcdVirtioBlkSupported|TRUE
  gArmSgiTokenSpaceGuid.PcdVirtioNetSupported|TRUE

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdVFPEnabled|1
  gEfiMdeModulePkgTokenSpaceGuid.PcdMaxVariableSize|0x2000

  # DRAM Block2 Base and Size
  gArmSgiTokenSpaceGuid.PcdDramBlock2Base|0x8080000000
  gArmSgiTokenSpaceGuid.PcdDramBlock2Size|0x180000000

  # NV Storage PCDs. Use base of 0x08000000 for NOR0, 0xC0000000 for NOR 1
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableBase|0x0C000000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageVariableSize|0x01400000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingBase|0x0D400000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwWorkingSize|0x01400000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareBase|0x0E800000
  gEfiMdeModulePkgTokenSpaceGuid.PcdFlashNvStorageFtwSpareSize|0x01400000

  # Stacks for MPCores in Normal World
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0x80000000
  gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x40000
  gArmPlatformTokenSpaceGuid.PcdCPUCoreSecondaryStackSize|0x0

  # System Memory (1GB - 16MB of Trusted DRAM at the top of the 32bit address space)
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x7F000000

  # GIC Base Addresses
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x30000000
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x300C0000

  #
  # PCIe
  #
  gArmTokenSpaceGuid.PcdPciBusMin|0
  gArmTokenSpaceGuid.PcdPciBusMax|255
  gArmTokenSpaceGuid.PcdPciIoBase|0x0
  gArmTokenSpaceGuid.PcdPciIoSize|0x00800000
  gArmTokenSpaceGuid.PcdPciIoTranslation|0x77800000
  gArmTokenSpaceGuid.PcdPciMmio32Base|0x70000000
  gArmTokenSpaceGuid.PcdPciMmio32Size|0x07800000
  gArmTokenSpaceGuid.PcdPciMmio32Translation|0x0
  gArmTokenSpaceGuid.PcdPciMmio64Base|0x500000000
  gArmTokenSpaceGuid.PcdPciMmio64Size|0x300000000
  gArmTokenSpaceGuid.PcdPciMmio64Translation|0x0
  gEfiMdePkgTokenSpaceGuid.PcdPciExpressBaseAddress|0x60000000
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|24

  ## PL011 - Serial Terminal
  gEfiMdeModulePkgTokenSpaceGuid.PcdSerialRegisterBase|0x7FF80000
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultBaudRate|115200
  gEfiMdePkgTokenSpaceGuid.PcdUartDefaultReceiveFifoDepth|0
  gArmPlatformTokenSpaceGuid.PL011UartInteger|4
  gArmPlatformTokenSpaceGuid.PL011UartFractional|0

  ## PL370 - HDLCD1
  gArmPlatformTokenSpaceGuid.PcdArmHdLcdBase|0x7FF60000

  ## PL011 - Serial Debug UART
  gArmPlatformTokenSpaceGuid.PcdSerialDbgRegisterBase|0x7FF80000
  gArmPlatformTokenSpaceGuid.PcdSerialDbgUartClkInHz|7372800
  gArmPlatformTokenSpaceGuid.PcdSerialDbgUartBaudRate|115200
  gArmPlatformTokenSpaceGuid.PL011UartInterrupt|147

  ## PL031 RealTimeClock
  gArmPlatformTokenSpaceGuid.PcdPL031RtcBase|0x1C170000

  # List of Device Paths that support BootMonFs
  gArmBootMonFsTokenSpaceGuid.PcdBootMonFsSupportedDevicePaths|L"VenHw(93E34C7E-B50E-11DF-9223-2443DFD72085,00)"

  # ARM OS Loader
  gEfiMdePkgTokenSpaceGuid.PcdPlatformBootTimeOut|3

  # ARM Architectural Timer Frequency
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|100000000
  gEmbeddedTokenSpaceGuid.PcdMetronomeTickPeriod|1000
  gEmbeddedTokenSpaceGuid.PcdTimerPeriod|1000

  # ARM Cores and Clusters
  gArmPlatformTokenSpaceGuid.PcdCoreCount|4
  gArmPlatformTokenSpaceGuid.PcdClusterCount|2

  # Virtio Disk
  gArmSgiTokenSpaceGuid.PcdVirtioBlkBaseAddress|0x1c130000
  gArmSgiTokenSpaceGuid.PcdVirtioBlkSize|0x10000
  gArmSgiTokenSpaceGuid.PcdVirtioBlkInterrupt|202

  # Ethernet / Virtio Network
!ifdef EDK2_ENABLE_SMSC_91X
  gEmbeddedTokenSpaceGuid.PcdLan91xDxeBaseAddress|0x18000000
!endif
  gArmSgiTokenSpaceGuid.PcdVirtioNetBaseAddress|0x1c150000
  gArmSgiTokenSpaceGuid.PcdVirtioNetSize|0x10000
  gArmSgiTokenSpaceGuid.PcdVirtioNetInterrupt|204

  #
  # Set the base address and size of the buffer used
  # for communication between the Normal world edk2
  # with StandaloneMm image at S-EL0 through MM_COMMUNICATE.
  # This buffer gets allocated in ATF and since we do not have
  # a mechanism currently to communicate the base address and
  # size of this buffer from ATF, hard-code it here
  #
  ## MM Communicate
  gArmTokenSpaceGuid.PcdMmBufferBase|0xFF600000
  gArmTokenSpaceGuid.PcdMmBufferSize|0x10000

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  #
  # PEI Phase modules
  #
  ArmPkg/Drivers/CpuPei/CpuPei.inf
  ArmPlatformPkg/MemoryInitPei/MemoryInitPeim.inf
  ArmPlatformPkg/PrePeiCore/PrePeiCoreUniCore.inf
  ArmPlatformPkg/PlatformPei/PlatformPeim.inf
  MdeModulePkg/Core/Pei/PeiMain.inf
  MdeModulePkg/Universal/PCD/Pei/Pcd.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  }
  MdeModulePkg/Universal/FaultTolerantWritePei/FaultTolerantWritePei.inf
  MdeModulePkg/Universal/Variable/Pei/VariablePei.inf
  MdeModulePkg/Core/DxeIplPeim/DxeIpl.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  }
  Platform/ARM/SgiPkg/Library/SgiPlatformPei/SgiPlatformPei.inf

  #
  # DXE
  #
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x8000000F
  }

  #
  # Architectural Protocols
  #
  ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
  ArmPkg/Drivers/TimerDxe/TimerDxe.inf
  ArmPkg/Drivers/GenericWatchdogDxe/GenericWatchdogDxe.inf
  ArmPlatformPkg/Drivers/LcdGraphicsOutputDxe/LcdGraphicsOutputDxe.inf
  ArmPlatformPkg/Drivers/NorFlashDxe/NorFlashDxe.inf
  EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
  EmbeddedPkg/ResetRuntimeDxe/ResetRuntimeDxe.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  MdeModulePkg/Universal/MonotonicCounterRuntimeDxe/MonotonicCounterRuntimeDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
  OvmfPkg/VirtioBlkDxe/VirtioBlk.inf

  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/Console/TerminalDxe/TerminalDxe.inf
  MdeModulePkg/Universal/SerialDxe/SerialDxe.inf
  MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/VarCheckUefiLib/VarCheckUefiLib.inf
      NULL|EmbeddedPkg/Library/NvVarStoreFormattedLib/NvVarStoreFormattedLib.inf
      BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  }
  MdeModulePkg/Universal/FaultTolerantWriteDxe/FaultTolerantWriteDxe.inf

  #
  # ACPI Support
  #
  MdeModulePkg/Universal/Acpi/AcpiTableDxe/AcpiTableDxe.inf
  Platform/ARM/SgiPkg/AcpiTables/Sgi575AcpiTables.inf
  Platform/ARM/SgiPkg/AcpiTables/RdN1EdgeAcpiTables.inf
  Platform/ARM/SgiPkg/AcpiTables/RdE1EdgeAcpiTables.inf
  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf

  #
  # platform driver
  #
  Platform/ARM/SgiPkg/Drivers/PlatformDxe/PlatformDxe.inf

  #
  # FAT filesystem + GPT/MBR partitioning
  #
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  FatPkg/EnhancedFatDxe/Fat.inf

  #
  # Bds
  #
  MdeModulePkg/Universal/BdsDxe/BdsDxe.inf
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  MdeModulePkg/Universal/DisplayEngineDxe/DisplayEngineDxe.inf
  MdeModulePkg/Universal/SetupBrowserDxe/SetupBrowserDxe.inf
  MdeModulePkg/Application/UiApp/UiApp.inf {
    <LibraryClasses>
      NULL|MdeModulePkg/Library/DeviceManagerUiLib/DeviceManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootManagerUiLib/BootManagerUiLib.inf
      NULL|MdeModulePkg/Library/BootMaintenanceManagerUiLib/BootMaintenanceManagerUiLib.inf
      PcdLib|MdePkg/Library/DxePcdLib/DxePcdLib.inf
  }

  # SMSC LAN 91C111 / Virtio Network
!ifdef EDK2_ENABLE_SMSC_91X
  EmbeddedPkg/Drivers/Lan91xDxe/Lan91xDxe.inf
!endif
  OvmfPkg/VirtioNetDxe/VirtioNet.inf

  #
  # Required by PCI
  #
  ArmPkg/Drivers/ArmPciCpuIo2Dxe/ArmPciCpuIo2Dxe.inf

  #
  # PCI Support
  #
  MdeModulePkg/Bus/Pci/PciBusDxe/PciBusDxe.inf
  MdeModulePkg/Bus/Pci/PciHostBridgeDxe/PciHostBridgeDxe.inf {
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x8010004F
  }

  #
  # AHCI Support
  #
  MdeModulePkg/Bus/Ata/AtaAtapiPassThru/AtaAtapiPassThru.inf
  MdeModulePkg/Bus/Ata/AtaBusDxe/AtaBusDxe.inf

  #
  # SATA Controller
  #
  MdeModulePkg/Bus/Pci/SataControllerDxe/SataControllerDxe.inf

  ArmPkg/Drivers/MmCommunicationDxe/MmCommunication.inf
