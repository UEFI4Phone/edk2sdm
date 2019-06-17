## @file
#  dsc include file for Configuration Manager
#
#  Copyright (c) 2017 - 2018, ARM Limited. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
##

[Defines]

[BuildOptions]

[LibraryClasses.common]

[Components.common]
  # Configuration Manager
  Platform/ARM/JunoPkg/ConfigurationManager/ConfigurationManagerDxe/ConfigurationManagerDxe.inf {
    <LibraryClasses>
    # Platform ASL Tables
    PlatformAslTablesLib|Platform/ARM/JunoPkg/ConfigurationManager/PlatformASLTablesLib/PlatformASLTablesLib.inf
  <BuildOptions>
   *_*_*_PLATFORM_FLAGS = -I$(BIN_DIR)/Platform/ARM/JunoPkg/ConfigurationManager/PlatformASLTablesLib/PlatformASLTablesLib/OUTPUT
  }
