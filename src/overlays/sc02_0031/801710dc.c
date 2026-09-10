/* SC02.CD FILE_031 / ov_SC02_031 retail span [801710DC,80171120).
 * Offset 0x48F84 at overlay base 80128158. SHA256(span)=9eb7ef3f00561e2aa3388ad941f2f63270de8597c02aca57ad43a380608b575e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801710dc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x3C048012)
MUSASHI_NATIVE_MIPS_WORD(0x9484F738)
MUSASHI_NATIVE_MIPS_WORD(0x3C058012)
MUSASHI_NATIVE_MIPS_WORD(0x94A5F73A)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00B532)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8002D4C8(u16, u16);                          /* extern */
void func_80171928(s32);                               /* static */
extern u16 D_8011F738;
extern u16 D_8011F73A;

void func_801710DC(s32 arg0) {
    func_8002D4C8(D_8011F738, D_8011F73A);
    func_80171928(arg0);
}
#endif
