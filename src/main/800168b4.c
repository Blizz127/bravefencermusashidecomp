/* Main-exec range [800168B4,800168C4) from the SLUS executable.
 * SHA256(span)=c9c92b1158d4488fd114b6fc8bc3496cd8ac638147be37d51fb379a9c41fb337.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0xA420F7CE)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s16 D_800AF7CE;

void func_800168B4(void) {
    D_800AF7CE = 0;
}
#endif
