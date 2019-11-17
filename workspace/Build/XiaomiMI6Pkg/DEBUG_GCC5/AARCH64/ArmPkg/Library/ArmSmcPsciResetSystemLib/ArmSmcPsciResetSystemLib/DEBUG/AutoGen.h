/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_18B12C83_7718_4D83_ADA4_87F2FE698DD4
#define _AUTOGENH_18B12C83_7718_4D83_ADA4_87F2FE698DD4

#ifdef __cplusplus
extern "C" {
#endif

#include <Base.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;


// Guids
extern GUID gArmTokenSpaceGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// PCD definitions
#define _PCD_TOKEN_PcdFvBaseAddress  8U
extern const UINT64 _gPcd_FixedAtBuild_PcdFvBaseAddress;
#define _PCD_GET_MODE_64_PcdFvBaseAddress  _gPcd_FixedAtBuild_PcdFvBaseAddress
//#define _PCD_SET_MODE_64_PcdFvBaseAddress  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD
#define _PCD_VALUE_PcdFvBaseAddress 0xD0008000
#define _PCD_SIZE_PcdFvBaseAddress 8
#define _PCD_GET_MODE_SIZE_PcdFvBaseAddress _PCD_SIZE_PcdFvBaseAddress
#define _PCD_TOKEN_PcdArmReenterPeiForCapsuleWarmReboot  80U
extern const BOOLEAN _gPcd_FixedAtBuild_PcdArmReenterPeiForCapsuleWarmReboot;
#define _PCD_GET_MODE_BOOL_PcdArmReenterPeiForCapsuleWarmReboot  _gPcd_FixedAtBuild_PcdArmReenterPeiForCapsuleWarmReboot
//#define _PCD_SET_MODE_BOOL_PcdArmReenterPeiForCapsuleWarmReboot  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD


#ifdef __cplusplus
}
#endif

#endif
