/** @file

Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#ifndef   __SOCKET_MEMORY_CONFIG_DATA_H__
#define   __SOCKET_MEMORY_CONFIG_DATA_H__


#include <UncoreCommonIncludes.h>
#include "SocketConfiguration.h"
#include <MemDefaults.h>

extern EFI_GUID gEfiSocketMemoryVariableGuid;
#define SOCKET_MEMORY_CONFIGURATION_NAME L"SocketMemoryConfig"

#pragma pack(1)
typedef struct {
    UINT8                   RtoMaxNodeInterleave;
    UINT8                   MemoryHotPlugBase;
    UINT8                   MemoryHotPlugLen;
    UINT8                   Srat;
    UINT8                   SratMemoryHotPlug;
    UINT8                   SratCpuHotPlug;
    UINT8                   PagePolicy;
    UINT8                   PatrolScrub;
    UINT8                   PatrolScrubDuration;
    UINT8                   PatrolScrubAddrMode;
    UINT8                   partialmirror;
    UINT8                   partialmirrorsad0;
    UINT8                   PartialMirrorUefi;
    UINT16                  PartialMirrorUefiPercent;
    UINT16                  partialmirrorsize[MAX_PARTIAL_MIRROR]; // Array of sizes of different partial mirrors
    UINT8                   DemandScrubMode;
    UINT8                   SddcPlusOneEn;
    UINT16                  spareErrTh;
    UINT8                   DieSparing;
    UINT8                   DieSparingAggressivenessLevel;
    UINT8                   ADDDCEn;
    UINT8                   AdddcErrInjEn;
    UINT8                   leakyBktLo;
    UINT8                   leakyBktHi;
    UINT8                   DutyCycleTraining;
    UINT8                   refreshMode;
    UINT8                   dllResetTestLoops;
    UINT8                   DdrMemoryType;
    UINT8                   HwMemTest;
    UINT16                  MemTestLoops;
    UINT8                   EccSupport;
    UINT8                   SocketInterleaveBelow4GB;
    UINT8                   RtoDimmManagement;
    UINT8                   RtoPartitionDDRTDimm;
    UINT8                   RtoPartitionRatio[16];    //[MAX_SOCKET * MAX_IMC] = [8]
    UINT8                   volMemMode;
    UINT8                   RtoPerMemMode;
    UINT8                   memInterleaveGran1LM;
    UINT8                   RtoMemInterleaveGranPMemUMA;
    UINT8                   RtoCfgMask2LM;
    UINT8                   ImcInterleaving;
    UINT8                   ChannelInterleaving;
    UINT8                   RankInterleaving;
    UINT8                   CkeProgramming;
    UINT8                   SrefProgramming;
    UINT8                   PkgcSrefEn;
    UINT8                   CkeIdleTimer;
    UINT8                   ApdEn;
    UINT8                   PpdEn;
    UINT8                   DdrtCkeEn;
    UINT8                   OppSrefEn;
    UINT8                   DdrtSrefEn;
    UINT8                   MdllOffEn;
    UINT8                   CkMode;
    UINT8                   MemTestOnFastBoot;
    UINT8                   AttemptFastBoot;
    UINT8                   AttemptFastBootCold;
    UINT8                   bdatEn;
    UINT8                   ScrambleEnDDRT;
    UINT8                   ScrambleEn;  // for ddr4
    UINT8                   allowCorrectableError;
    UINT16                  ScrambleSeedLow;
    UINT16                  ScrambleSeedHigh;
    UINT8                   CustomRefreshRateEn;
    UINT8                   CustomRefreshRate;
    UINT8                   mcBgfThreshold;
    UINT8                   readVrefCenter;
    UINT8                   wrVrefCenter;
    UINT8                   haltOnMemErr;
    UINT8                   thermalthrottlingsupport;
    UINT8                   thermalmemtrip;
    UINT8                   DimmTempStatValue;
    UINT8                   XMPProfilesSup;
    UINT8                   XMPMode;
    UINT8                   tCAS;
    UINT8                   tRP;
    UINT8                   tRCD;
    UINT8                   tRAS;
    UINT8                   tWR;
    UINT16                  tRFC;
    UINT8                   tRRD;
    UINT8                   tRTP;
    UINT8                   tWTR;
    UINT8                   tFAW;
    UINT8                   tCWL;
    UINT8                   tRC;
    UINT8                   commandTiming;
    UINT16                  tREFI;
    UINT8                   DdrFreqLimit;
    UINT16                  Vdd;
    UINT8                   lrdimmModuleDelay;
    UINT32                  rmtPatternLength;
    UINT32                  rmtPatternLengthExt;
    UINT8                   check_pm_sts;
    UINT8                   check_platform_detect;
    UINT8                   MemPwrSave;
    UINT8                   ElectricalThrottlingMode;
    UINT8                   MultiThreaded;
    UINT8                   promoteMrcWarnings;
    UINT8                   promoteWarnings;
    UINT8                   oppReadInWmm;
    UINT16                  normOppInterval;
    UINT8                   sck0ch0;
    UINT8                   sck0ch1;
    UINT8                   sck0ch2;
    UINT8                   sck0ch3;
    UINT8                   sck0ch4;
    UINT8                   sck0ch5;
    UINT8                   sck1ch0;
    UINT8                   sck1ch1;
    UINT8                   sck1ch2;
    UINT8                   sck1ch3;
    UINT8                   sck1ch4;
    UINT8                   sck1ch5;
    UINT8                   sck2ch0;
    UINT8                   sck2ch1;
    UINT8                   sck2ch2;
    UINT8                   sck2ch3;
    UINT8                   sck2ch4;
    UINT8                   sck2ch5;
    UINT8                   sck3ch0;
    UINT8                   sck3ch1;
    UINT8                   sck3ch2;
    UINT8                   sck3ch3;
    UINT8                   sck3ch4;
    UINT8                   sck3ch5;
    UINT8                   mdllSden;
    UINT8                   memhotSupport;
    UINT8                   MemhotOutputOnlyOpt;
    UINT8                   ADREn;
    UINT8                   RankMargin;
    UINT8                   EnableBacksideRMT;
    UINT8                   EnableBacksideCMDRMT;
    UINT8                   Reserved_0;
    UINT8                   rankMaskEn;
    UINT8                   RankSparing;
    UINT8                   multiSparingRanks;
    UINT8                   caParity;
    UINT8                   dimmIsolation;
    UINT8                   smbSpeed;
    UINT8                   EnforcePOR;
    UINT8                   pda;
    UINT8                   turnaroundOpt;
    UINT8                   oneRankTimingMode;
    UINT8                   eyeDiagram;

    UINT8                   DramRaplInit;
    UINT8                   BwLimitTfOvrd;
    UINT8                   perbitmargin;
    UINT8                   DramRaplExtendedRange;
    UINT8                   CmsEnableDramPm;
    UINT8                   logParsing;
    UINT8                   WritePreamble;
    UINT8                   ReadPreamble;
    UINT8                   WrCRC;

    UINT8                   Reserved_1;
    UINT8                   Reserved_2;
    UINT8                   Reserved_3;
    UINT8                   Reserved_4;
    UINT8                   Reserved_5;
    UINT8                   Reserved_6;
    UINT8                   Reserved_7;
    UINT8                   Reserved_8;

    UINT8                   RmtOnColdFastBoot;
    UINT8                   mrcRepeatTest;
    UINT8                   RtoLowMemChannel;
    UINT8                   RtoHighAddressStartBitPosition;
    UINT8                   staggerref;
    UINT32                  memFlows;
    UINT32                  memFlowsExt;
    UINT8                   Blockgnt2cmd1cyc;
    UINT8                   Disddrtopprd;
    UINT8                   setTDPDIMMPower;
    UINT8                   setSecureEraseAllDIMMs;
    UINT8                   setSecureEraseSktCh[48];
    //
    // PPR related
    //
    UINT8                   pprType;
    UINT8                   pprErrInjTest;
    // CR QoS Configuration Profiles
    UINT8                   crQosConfig;
    UINT8                   Reserved_11;
    UINT8                   Reserved_12;
    UINT8                   Reserved_13;
    UINT8                   imcBclk;
    UINT8                   spdCrcCheck;
} SOCKET_MEMORY_CONFIGURATION;

#pragma pack()

#endif

