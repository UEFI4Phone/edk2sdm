## @file
#  Platform description.
#
# Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
#
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
##


  #
  # UEFI network modules
  #
  !include NetworkPkg/NetworkComponents.dsc.inc

!if gAdvancedFeaturePkgTokenSpaceGuid.PcdSmbiosEnable == TRUE
  MdeModulePkg/Universal/SmbiosDxe/SmbiosDxe.inf
!endif

