/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017427C,801742A4).
 * Offset 0x4C124 at overlay base 80128158. SHA256(span)=e831bd081fd0cb48b08642a7a8d839c3f5d0195666f24edf74ad6b02f44dec13.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017427c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C048017)
MUSASHI_NATIVE_MIPS_WORD(0x248442A4)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D1A1)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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
void func_80174684();
void func_801742A4();
void func_8017427C(void) {
    func_80174684(func_801742A4);
}
#endif
