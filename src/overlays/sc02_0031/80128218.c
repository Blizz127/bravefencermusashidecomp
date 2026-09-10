/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128218,80128228).
 * Offset 0xC0 at overlay base 80128158. SHA256(span)=4ae8b53beaa7aaa9d0002c34cc6312409c6d70589ba57991308b874beb789405.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_80182D1C->D_801A3234.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801A)
MUSASHI_NATIVE_MIPS_WORD(0x8C423234)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_801A3234;

s32 func_80128218(void) {
    return D_801A3234;
}

#endif
