/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A2F4,8012A304).
 * Offset 0x219C at overlay base 80128158. SHA256(span)=c475584f48b5ca97bb86e311cac4ca804ab22ffe1508ec7533a8f4b7f019893c.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a2f4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA02052C0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s8 D_801152C0;

void func_8012A2F4(void) {
    D_801152C0 = 0;
}
#endif
