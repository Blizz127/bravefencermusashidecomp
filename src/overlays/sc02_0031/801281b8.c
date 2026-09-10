/* SC02.CD FILE_031 / ov_SC02_031 retail span [801281B8,801281D8).
 * Offset 0x60 at overlay base 80128158. SHA256(span)=a1f738ca401ee1cbca9c8895e61d5856f8a1c6a6f82471b2bfd1271374b272f0.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801281b8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A1C5)
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

void func_80128714();                                  /* static */

void func_801281B8(void) {
    func_80128714();
}
#endif
