/* SC02.CD FILE_031 / ov_SC02_031 retail span [801281D8,801281F8).
 * Offset 0x80 at overlay base 80128158. SHA256(span)=1b56ab6e4efa80d00071490c8f959e8a08aa68d1f296b40ab7089c45980a4217.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801281d8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04F99F)
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

void func_8013E67C();                                  /* static */

void func_801281D8(void) {
    func_8013E67C();
}
#endif
