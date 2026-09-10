/* SC02.CD FILE_031 / ov_SC02_031 retail span [80175668,80175690).
 * Offset 0x4D510 at overlay base 80128158. SHA256(span)=0e57650d62e01cfe9e52688bf6e8bce094e5cd6e5a34be3b9f4415ee86deeff2.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80175668.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C04800C)
MUSASHI_NATIVE_MIPS_WORD(0x84849A02)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D5F8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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

void func_801757E0(s16);                               /* static */
extern s16 D_800B9A02;

void func_80175668(void) {
    func_801757E0(D_800B9A02);
}
#endif
