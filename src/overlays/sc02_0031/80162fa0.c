/* SC02.CD FILE_031 / ov_SC02_031 retail span [80162FA0,80162FC0).
 * Offset 0x3AE48 at overlay base 80128158. SHA256(span)=e9d1f1b8b2151e6fcf162a715fd18af7cb665b2a41220f59db21be49428bdec4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80162fa0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C051E8C)
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
void func_80147A30();
void func_80162FA0(void *a, void *b) {
    func_80147A30(a, b, 0x7F0000);
}
#endif
