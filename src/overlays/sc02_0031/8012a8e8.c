/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A8E8,8012A908).
 * Offset 0x2790 at overlay base 80128158. SHA256(span)=12611acd33f6dc175dc070161a1a6ac0766b749b3bde67e1c97104453e03f3d3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a8e8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AAAB)
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

void func_8012AAAC();                                  /* static */

void func_8012A8E8(void) {
    func_8012AAAC();
}
#endif
