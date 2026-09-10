/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A100,8012A110).
 * Offset 0x1FA8 at overlay base 80128158. SHA256(span)=c83f9f3a656063918cdc4c4bcf08dc8aacd3f7e09b4a5330290a0df11607b5fc.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a100.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA02450D6)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s8 D_801150D6;

void func_8012A100(s8 arg0) {
    D_801150D6 = arg0;
}
#endif
