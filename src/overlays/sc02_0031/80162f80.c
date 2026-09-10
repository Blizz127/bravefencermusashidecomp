/* SC02.CD FILE_031 / ov_SC02_031 retail span [80162F80,80162FA0).
 * Offset 0x3AE28 at overlay base 80128158. SHA256(span)=5bd3ece3abe0a688db93d6fb1a92cd7a7ec5ad9c7af82237ef3f6fd1f895fda8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80162f80.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C051E6F)
MUSASHI_NATIVE_MIPS_WORD(0x3C06007F)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801479BC();
void func_80162F80(void *a, void *b) {
    func_801479BC(a, b, 0x7F0000);
}
#endif
