/* SC02.CD FILE_031 / ov_SC02_031 retail span [801282CC,801282EC).
 * Offset 0x174 at overlay base 80128158. SHA256(span)=f019b84f40a245c6b9179c21e0fe302b0791677ba0e17a86efb6585ba4693f76.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801282cc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0046DF)
MUSASHI_NATIVE_MIPS_WORD(0x24040011)
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

void func_80011B7C();                                 /* extern */

void func_801282CC(void) {
    func_80011B7C(0x11);
}
#endif
