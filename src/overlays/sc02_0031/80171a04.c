/* SC02.CD FILE_031 / ov_SC02_031 retail span [80171A04,80171A10).
 * Offset 0x498AC at overlay base 80128158. SHA256(span)=2854bee75158eab23c1dee6601314e7b4c84ab89625ca4f15a45d4fd9aa288d9.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80171a04.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820217)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A04(u8 *p) {
    p[535] = 1;
}
#endif
