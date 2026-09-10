/* SC02.CD FILE_031 / ov_SC02_031 retail span [80128248,80128268).
 * Offset 0xF0 at overlay base 80128158. SHA256(span)=8f02ba46626051764663f5c6711003bc2f86c77cc94334714bf10708d883a359.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80128248.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A2BD)
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

void func_80128AF4();                                  /* static */

void func_80128248(void) {
    func_80128AF4();
}
#endif
