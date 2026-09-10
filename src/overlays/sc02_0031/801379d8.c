/* SC02.CD FILE_031 / ov_SC02_031 retail span [801379D8,801379EC).
 * Offset 0xF880 at overlay base 80128158. SHA256(span)=1564c18fe9af03fcfdafcfeea0d209014c837a9f549c4361b260fc73f27f4f4d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801379d8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA422752E)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s16 D_8012752E;

void func_801379D8(void) {
    D_8012752E = 1;
}
#endif
