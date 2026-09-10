/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A304,8012A328).
 * Offset 0x21AC at overlay base 80128158. SHA256(span)=4a855646b8c534c7beebd28f836c1c296b5ef365614b443f82a85edb5b233892.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a304.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA02252C0)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA4247080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xA42552C2)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s8 D_801152C0;
extern s16 D_801152C2;
extern s16 D_80127080;

void func_8012A304(s16 arg0, s16 arg1) {
    D_801152C0 = 1;
    D_80127080 = arg0;
    D_801152C2 = arg1;
}
#endif
