/* Main-exec range [8003AFF0,8003B02C) from the SLUS executable.
 * SHA256(span)=acc4472238894d98e2bc11ec684e9ae3926f4c327a5bb51ce1559936bab0b490.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B54C)
MUSASHI_NATIVE_MIPS_WORD(0x00042040)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x94840000)
MUSASHI_NATIVE_MIPS_WORD(0x10A20005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B574)
MUSASHI_NATIVE_MIPS_WORD(0x0800EC09)
MUSASHI_NATIVE_MIPS_WORD(0x00441004)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 *D_8006B54C;
extern s32 D_8006B574;
s32 func_8003AFF0(s32 a0, s32 a1) {
    u16 v = D_8006B54C[a0];
    if (a1 == -1) {
        return v;
    }
    return v << D_8006B574;
}
#endif
