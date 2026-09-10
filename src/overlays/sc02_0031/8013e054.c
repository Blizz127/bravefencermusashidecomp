/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E054,8013E064).
 * Offset 0x15EFC at overlay base 80128158. SHA256(span)=4dda550131ea1e430879a3cb3649e85fd020d29d43bffca4b2e4f82278cb3890.
 * Same shape as the registry-verified MAIN member 0012 carve with only the
 * listed data references retargeted for this member: D_801841C4->D_801A44EC.
 * Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801A)
MUSASHI_NATIVE_MIPS_WORD(0x8C4244EC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801A44EC;

s32 func_8013E054(void) {
    return D_801A44EC;
}

#endif
