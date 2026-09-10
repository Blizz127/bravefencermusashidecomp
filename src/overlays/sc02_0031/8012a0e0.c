/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A0E0,8012A100).
 * Offset 0x1F88 at overlay base 80128158. SHA256(span)=cabd5a4b736961a189c122ac197b6457675ade4146f4e76035c7011f4c1d1d8a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a0e0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A840)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012A100();                                 /* static */

void func_8012A0E0(void) {
    func_8012A100(0);
}
#endif
