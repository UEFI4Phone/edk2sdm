## @file
#  dsc include file for Configuration Manager
#
#  Copyright (c) 2017 - 2018, ARM Limited. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
##

[Defines]

[BuildOptions]
# Required for pre-processing ASL files that include ArmPlatform.h
  *_*_*_ASLPP_FLAGS        = $(PLATFORM_FLAGS)

[LibraryClasses.common]

[Components.common]
  # Configuration Manager
  Platform/ARM/VExpressPkg/ConfigurationManager/ConfigurationManagerDxe/ConfigurationManagerDxe.inf {
    <LibraryClasses>
    # Platform ASL Tables
    PlatformAslTablesLib|Platform/ARM/VExpressPkg/ConfigurationManager/PlatformASLTablesLib/PlatformASLTablesLib.inf
  <BuildOptions>
   *_*_*_PLATFORM_FLAGS = -I$(BIN_DIR)/Platform/ARM/VExpressPkg/ConfigurationManager/PlatformASLTablesLib/PlatformASLTablesLib/OUTPUT
  }
