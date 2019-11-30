/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_7E374E25_8E01_4FEE_87F2_390C23C606CD
#define _AUTOGENH_7E374E25_8E01_4FEE_87F2_390C23C606CD

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x7E374E25, 0x8E01, 0x4FEE, {0x87, 0xF2, 0x39, 0x0C, 0x23, 0xC6, 0x06, 0xCD}}

// Guids
extern GUID gArmPlatformTokenSpaceGuid;
extern GUID gArmTokenSpaceGuid;
extern GUID gEfiMdeModulePkgTokenSpaceGuid;
extern GUID gEfiMdePkgTokenSpaceGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdCoreCount  13U
#define _PCD_SIZE_PcdCoreCount 4
#define _PCD_GET_MODE_SIZE_PcdCoreCount  _PCD_SIZE_PcdCoreCount 
#define _PCD_VALUE_PcdCoreCount  1U
extern const  UINT32  _gPcd_FixedAtBuild_PcdCoreCount;
#define _PCD_GET_MODE_32_PcdCoreCount  _gPcd_FixedAtBuild_PcdCoreCount
//#define _PCD_SET_MODE_32_PcdCoreCount  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdGicDistributorBase  119U
#define _PCD_SIZE_PcdGicDistributorBase 8
#define _PCD_GET_MODE_SIZE_PcdGicDistributorBase  _PCD_SIZE_PcdGicDistributorBase 
#define _PCD_VALUE_PcdGicDistributorBase  0x17a00000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdGicDistributorBase;
#define _PCD_GET_MODE_64_PcdGicDistributorBase  _gPcd_FixedAtBuild_PcdGicDistributorBase
//#define _PCD_SET_MODE_64_PcdGicDistributorBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdGicInterruptInterfaceBase  121U
#define _PCD_SIZE_PcdGicInterruptInterfaceBase 8
#define _PCD_GET_MODE_SIZE_PcdGicInterruptInterfaceBase  _PCD_SIZE_PcdGicInterruptInterfaceBase 
#define _PCD_VALUE_PcdGicInterruptInterfaceBase  0ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdGicInterruptInterfaceBase;
#define _PCD_GET_MODE_64_PcdGicInterruptInterfaceBase  _gPcd_FixedAtBuild_PcdGicInterruptInterfaceBase
//#define _PCD_SET_MODE_64_PcdGicInterruptInterfaceBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdGicRedistributorsBase  120U
#define _PCD_SIZE_PcdGicRedistributorsBase 8
#define _PCD_GET_MODE_SIZE_PcdGicRedistributorsBase  _PCD_SIZE_PcdGicRedistributorsBase 
#define _PCD_VALUE_PcdGicRedistributorsBase  0x17b00000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdGicRedistributorsBase;
#define _PCD_GET_MODE_64_PcdGicRedistributorsBase  _gPcd_FixedAtBuild_PcdGicRedistributorsBase
//#define _PCD_SET_MODE_64_PcdGicRedistributorsBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdArmArchTimerSecIntrNum  124U
#define _PCD_SIZE_PcdArmArchTimerSecIntrNum 4
#define _PCD_GET_MODE_SIZE_PcdArmArchTimerSecIntrNum  _PCD_SIZE_PcdArmArchTimerSecIntrNum 
#define _PCD_VALUE_PcdArmArchTimerSecIntrNum  29U
extern const  UINT32  _gPcd_FixedAtBuild_PcdArmArchTimerSecIntrNum;
#define _PCD_GET_MODE_32_PcdArmArchTimerSecIntrNum  _gPcd_FixedAtBuild_PcdArmArchTimerSecIntrNum
//#define _PCD_SET_MODE_32_PcdArmArchTimerSecIntrNum  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdArmArchTimerIntrNum  125U
#define _PCD_SIZE_PcdArmArchTimerIntrNum 4
#define _PCD_GET_MODE_SIZE_PcdArmArchTimerIntrNum  _PCD_SIZE_PcdArmArchTimerIntrNum 
#define _PCD_VALUE_PcdArmArchTimerIntrNum  0x12U
extern const  UINT32  _gPcd_FixedAtBuild_PcdArmArchTimerIntrNum;
#define _PCD_GET_MODE_32_PcdArmArchTimerIntrNum  _gPcd_FixedAtBuild_PcdArmArchTimerIntrNum
//#define _PCD_SET_MODE_32_PcdArmArchTimerIntrNum  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdArmArchTimerHypIntrNum  127U
#define _PCD_SIZE_PcdArmArchTimerHypIntrNum 4
#define _PCD_GET_MODE_SIZE_PcdArmArchTimerHypIntrNum  _PCD_SIZE_PcdArmArchTimerHypIntrNum 
#define _PCD_VALUE_PcdArmArchTimerHypIntrNum  26U
extern const  UINT32  _gPcd_FixedAtBuild_PcdArmArchTimerHypIntrNum;
#define _PCD_GET_MODE_32_PcdArmArchTimerHypIntrNum  _gPcd_FixedAtBuild_PcdArmArchTimerHypIntrNum
//#define _PCD_SET_MODE_32_PcdArmArchTimerHypIntrNum  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdArmArchTimerVirtIntrNum  126U
#define _PCD_SIZE_PcdArmArchTimerVirtIntrNum 4
#define _PCD_GET_MODE_SIZE_PcdArmArchTimerVirtIntrNum  _PCD_SIZE_PcdArmArchTimerVirtIntrNum 
#define _PCD_VALUE_PcdArmArchTimerVirtIntrNum  0x13U
extern const  UINT32  _gPcd_FixedAtBuild_PcdArmArchTimerVirtIntrNum;
#define _PCD_GET_MODE_32_PcdArmArchTimerVirtIntrNum  _gPcd_FixedAtBuild_PcdArmArchTimerVirtIntrNum
//#define _PCD_SET_MODE_32_PcdArmArchTimerVirtIntrNum  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdGenericWatchdogControlBase  144U
#define _PCD_SIZE_PcdGenericWatchdogControlBase 8
#define _PCD_GET_MODE_SIZE_PcdGenericWatchdogControlBase  _PCD_SIZE_PcdGenericWatchdogControlBase 
#define _PCD_VALUE_PcdGenericWatchdogControlBase  0x2A440000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdGenericWatchdogControlBase;
#define _PCD_GET_MODE_64_PcdGenericWatchdogControlBase  _gPcd_FixedAtBuild_PcdGenericWatchdogControlBase
//#define _PCD_SET_MODE_64_PcdGenericWatchdogControlBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdGenericWatchdogRefreshBase  145U
#define _PCD_SIZE_PcdGenericWatchdogRefreshBase 8
#define _PCD_GET_MODE_SIZE_PcdGenericWatchdogRefreshBase  _PCD_SIZE_PcdGenericWatchdogRefreshBase 
#define _PCD_VALUE_PcdGenericWatchdogRefreshBase  0x2A450000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdGenericWatchdogRefreshBase;
#define _PCD_GET_MODE_64_PcdGenericWatchdogRefreshBase  _gPcd_FixedAtBuild_PcdGenericWatchdogRefreshBase
//#define _PCD_SET_MODE_64_PcdGenericWatchdogRefreshBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdSerialRegisterBase  146U
#define _PCD_SIZE_PcdSerialRegisterBase 8
#define _PCD_GET_MODE_SIZE_PcdSerialRegisterBase  _PCD_SIZE_PcdSerialRegisterBase 
#define _PCD_VALUE_PcdSerialRegisterBase  0x03F8ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdSerialRegisterBase;
#define _PCD_GET_MODE_64_PcdSerialRegisterBase  _gPcd_FixedAtBuild_PcdSerialRegisterBase
//#define _PCD_SET_MODE_64_PcdSerialRegisterBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUartDefaultBaudRate  97U
#define _PCD_SIZE_PcdUartDefaultBaudRate 8
#define _PCD_GET_MODE_SIZE_PcdUartDefaultBaudRate  _PCD_SIZE_PcdUartDefaultBaudRate 
#define _PCD_VALUE_PcdUartDefaultBaudRate  115200ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdUartDefaultBaudRate;
#define _PCD_GET_MODE_64_PcdUartDefaultBaudRate  _gPcd_FixedAtBuild_PcdUartDefaultBaudRate
//#define _PCD_SET_MODE_64_PcdUartDefaultBaudRate  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PL011UartClkInHz  147U
#define _PCD_SIZE_PL011UartClkInHz 4
#define _PCD_GET_MODE_SIZE_PL011UartClkInHz  _PCD_SIZE_PL011UartClkInHz 
#define _PCD_VALUE_PL011UartClkInHz  24000000U
extern const  UINT32  _gPcd_FixedAtBuild_PL011UartClkInHz;
#define _PCD_GET_MODE_32_PL011UartClkInHz  _gPcd_FixedAtBuild_PL011UartClkInHz
//#define _PCD_SET_MODE_32_PL011UartClkInHz  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PL011UartInterrupt  148U
#define _PCD_SIZE_PL011UartInterrupt 4
#define _PCD_GET_MODE_SIZE_PL011UartInterrupt  _PCD_SIZE_PL011UartInterrupt 
#define _PCD_VALUE_PL011UartInterrupt  0x00000000U
extern const  UINT32  _gPcd_FixedAtBuild_PL011UartInterrupt;
#define _PCD_GET_MODE_32_PL011UartInterrupt  _gPcd_FixedAtBuild_PL011UartInterrupt
//#define _PCD_SET_MODE_32_PL011UartInterrupt  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdSerialDbgRegisterBase  149U
#define _PCD_SIZE_PcdSerialDbgRegisterBase 8
#define _PCD_GET_MODE_SIZE_PcdSerialDbgRegisterBase  _PCD_SIZE_PcdSerialDbgRegisterBase 
#define _PCD_VALUE_PcdSerialDbgRegisterBase  0x00000000ULL
extern const  UINT64  _gPcd_FixedAtBuild_PcdSerialDbgRegisterBase;
#define _PCD_GET_MODE_64_PcdSerialDbgRegisterBase  _gPcd_FixedAtBuild_PcdSerialDbgRegisterBase
//#define _PCD_SET_MODE_64_PcdSerialDbgRegisterBase  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdWatchdogCount  150U
#define _PCD_SIZE_PcdWatchdogCount 4
#define _PCD_GET_MODE_SIZE_PcdWatchdogCount  _PCD_SIZE_PcdWatchdogCount 
#define _PCD_VALUE_PcdWatchdogCount  0x0U
extern const  UINT32  _gPcd_FixedAtBuild_PcdWatchdogCount;
#define _PCD_GET_MODE_32_PcdWatchdogCount  _gPcd_FixedAtBuild_PcdWatchdogCount
//#define _PCD_SET_MODE_32_PcdWatchdogCount  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD


#ifdef __cplusplus
}
#endif

#endif
