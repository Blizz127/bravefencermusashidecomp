/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139A34,80139A44).
 * Offset 0x118DC at overlay base 80128158. SHA256(span)=7072162d1a6b36d2b2662ab0b6c44b6fefa98b63485d9a45c926bf4bda008b3b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139a34.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC247520)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80127520;

void func_80139A34(s32 arg0) {
    D_80127520 = arg0;
}
#endif
