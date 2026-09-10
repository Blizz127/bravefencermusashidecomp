/* SC02 resident retail span [8013E054,8013E064). Offset 0x15EFC at base 80128158.
 * SHA256(span)=dfe83c6abe02ccfdedbaed0ea894cd5df31aa6f0f64eeb750bc7133f5df761c5.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_801841C4->D_801B637C.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02801B)
MUSASHI_NATIVE_MIPS_WORD(0x8C42637C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801B637C;

s32 func_8013E054(void) {
    return D_801B637C;
}

#endif
