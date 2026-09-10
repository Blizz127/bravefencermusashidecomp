/* SC02.CD FILE_031 / ov_SC02_031 retail span [80139DC8,80139DEC).
 * Offset 0x11C70 at overlay base 80128158. SHA256(span)=47fc75c5557040fd12f3d1814eb36a0a23cb522a4ac548d1110642ffc458d83d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80139dc8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24030287)
MUSASHI_NATIVE_MIPS_WORD(0x3C028013)
MUSASHI_NATIVE_MIPS_WORD(0x2442811A)
MUSASHI_NATIVE_MIPS_WORD(0xA4400000)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0461FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s16 D_8012811A[];
void func_80139DC8(void) {
    s32 i = 0x287;
    s16 *p = D_8012811A;
    do { *p = 0; i--; p--; } while (i >= 0);
}
#endif
