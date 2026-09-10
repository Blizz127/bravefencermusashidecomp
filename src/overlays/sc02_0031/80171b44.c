/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171B44,80171B4C).
 * Offset 0x499EC at overlay base 80128158. SHA256(span)=625c5a906c4fcfa60bb2e12c96ad7d61ac2a2a4d21a4dc1e2d0eed0436aa353f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171b44.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA080020C)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171B44(u8 *p) {
    p[524] = 0;
}
#endif
