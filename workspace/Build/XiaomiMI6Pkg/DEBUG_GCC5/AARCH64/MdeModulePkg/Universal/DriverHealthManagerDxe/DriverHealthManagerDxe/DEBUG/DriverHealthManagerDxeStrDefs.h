/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    DriverHealthManagerDxeStrDefs.h
  Abstract:       Auto-generated DriverHealthManagerDxeStrDefs.h for building module or library.
**/

#ifndef _STRDEFS_EBF8ED7C_0DD1_4787_84F1_F48D537DCACF
#define _STRDEFS_EBF8ED7C_0DD1_4787_84F1_F48D537DCACF


//
//Unicode String ID
//
// #define $LANGUAGE_NAME                                       0x0000 // not referenced
// #define $PRINTABLE_LANGUAGE_NAME                             0x0001 // not referenced
#define STR_FORM_TITLE                                       0x0002
#define STR_FORM_HELP                                        0x0003
#define STR_NULL                                             0x0004
#define STR_REPAIR_REQUIRED                                  0x0005
#define STR_CONFIGURATION_REQUIRED                           0x0006
#define STR_FAILED                                           0x0007
#define STR_RECONNECT_REQUIRED                               0x0008
#define STR_REBOOT_REQUIRED                                  0x0009
#define STR_HEALTHY                                          0x000A

extern unsigned char DriverHealthManagerDxeStrings[];


#define STRING_ARRAY_NAME DriverHealthManagerDxeStrings

#ifdef VFRCOMPILE
#define gEfiHiiDriverHealthFormsetGuid { 0xf22fc20c, 0x8cf4, 0x45eb, { 0x8e, 0x6, 0xad, 0x4e, 0x50, 0xb9, 0x5d, 0xd3 }}
#define gEfiIfrTianoGuid { 0xf0b1735, 0x87a0, 0x4193, {0xb2, 0x66, 0x53, 0x8c, 0x38, 0xaf, 0x48, 0xce }}
#define gEfiHiiConfigAccessProtocolGuid {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85}}
#define FixedPcdGetBool(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet8(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet16(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet32(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet64(TokenName) _PCD_VALUE_##TokenName
#define FeaturePcdGet(TokenName) _PCD_VALUE_##TokenName
#define _PCD_VALUE_PcdDriverHealthConfigureForm { 0xf4, 0xd9, 0x96, 0x42, 0xfc, 0xf6, 0xde, 0x4d, 0x86, 0x85, 0x8c, 0xe2, 0xd7, 0x9d, 0x90, 0xf0 }
#endif

#endif
