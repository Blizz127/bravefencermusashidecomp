/* SC02.CD FILE_031 / ov_SC02_031 retail span [80129428,8012943C).
 * Offset 0x12D0 at overlay base 80128158. SHA256(span)=0c949b33294ad1a1a31774d76f7516eafe85ce7f073be72a767a950c3b0435b5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80129428.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA4224EE0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s16 D_80114EE0;

void func_80129428(void) {
    D_80114EE0 = 1;
}
#endif
