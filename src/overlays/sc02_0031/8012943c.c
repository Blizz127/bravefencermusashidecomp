/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012943C,8012944C).
 * Offset 0x12E4 at overlay base 80128158. SHA256(span)=6f5ae75d843634b01e87cc6ba089c244941f5535bf7a3bed8f77eeca499492fd.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012943c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA4204EE0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s16 D_80114EE0;

void func_8012943C(void) {
    D_80114EE0 = 0;
}
#endif
