/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    UiAppStrDefs.h
  Abstract:       Auto-generated UiAppStrDefs.h for building module or library.
**/

#ifndef _STRDEFS_462CAA21_7614_4503_836E_8AB6F4662331
#define _STRDEFS_462CAA21_7614_4503_836E_8AB6F4662331


//
//Unicode String ID
//
// #define $LANGUAGE_NAME                                       0x0000 // not referenced
// #define $PRINTABLE_LANGUAGE_NAME                             0x0001 // not referenced
#define STR_FRONT_PAGE_TITLE                                 0x0002
#define STR_FRONT_PAGE_COMPUTER_MODEL                        0x0003
#define STR_FRONT_PAGE_CPU_MODEL                             0x0004
#define STR_FRONT_PAGE_CPU_SPEED                             0x0005
#define STR_FRONT_PAGE_MEMORY_SIZE                           0x0006
#define STR_FRONT_PAGE_BIOS_VERSION                          0x0007
#define STR_CONTINUE_PROMPT                                  0x0008
#define STR_LANGUAGE_SELECT                                  0x0009
#define STR_LANGUAGE_SELECT_HELP                             0x000A
#define STR_MISSING_STRING                                   0x000B
#define STR_EMPTY_STRING                                     0x000C
#define STR_RESET_STRING                                     0x000D
#define STR_CUSTOMIZE_BANNER_LINE4_LEFT                      0x000E
#define STR_CUSTOMIZE_BANNER_LINE4_RIGHT                     0x000F
#define STR_CUSTOMIZE_BANNER_LINE5_LEFT                      0x0010
#define STR_CUSTOMIZE_BANNER_LINE5_RIGHT                     0x0011
#define STR_TEST_KEY_USED                                    0x0012
#define STR_NULL_STRING                                      0x0013
// #define STR_FRONT_PAGE_BANNER_0_LEFT                         0x0014 // not referenced
// #define STR_FRONT_PAGE_BANNER_0_RIGHT                        0x0015 // not referenced
// #define STR_FRONT_PAGE_BANNER_1_LEFT                         0x0016 // not referenced
// #define STR_FRONT_PAGE_BANNER_1_RIGHT                        0x0017 // not referenced
// #define STR_FRONT_PAGE_BANNER_2_LEFT                         0x0018 // not referenced
// #define STR_FRONT_PAGE_BANNER_3_LEFT                         0x0019 // not referenced
// #define STR_CONTINUE_HELP                                    0x001A // not referenced
// #define STR_RESET_STRING_HELP                                0x001B // not referenced

extern unsigned char UiAppStrings[];


#define STRING_ARRAY_NAME UiAppStrings

#ifdef VFRCOMPILE
#define gEfiIfrTianoGuid { 0xf0b1735, 0x87a0, 0x4193, {0xb2, 0x66, 0x53, 0x8c, 0x38, 0xaf, 0x48, 0xce }}
#define gEfiIfrFrontPageGuid { 0xe58809f8, 0xfbc1, 0x48e2, { 0x88, 0x3a, 0xa3, 0x0f, 0xdc, 0x4b, 0x44, 0x1e } }
#define gEfiSmbiosProtocolGuid {0x3583ff6, 0xcb36, 0x4940, { 0x94, 0x7e, 0xb9, 0xb3, 0x9f, 0x4a, 0xfa, 0xf7}}
#define gEfiHiiConfigAccessProtocolGuid {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85}}
#define FixedPcdGetBool(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet8(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet16(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet32(TokenName) _PCD_VALUE_##TokenName
#define FixedPcdGet64(TokenName) _PCD_VALUE_##TokenName
#define FeaturePcdGet(TokenName) _PCD_VALUE_##TokenName
#define _PCD_VALUE_PcdUefiVariableDefaultPlatformLangCodes "en;fr;en-US;fr-FR"
#define _PCD_VALUE_PcdFirmwareVersionString L"Alpha"
#endif

#endif
