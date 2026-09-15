/* Main-exec range [800351E8,80035210) from the SLUS executable.
 * SHA256(span)=d247f93e5840743dcfd3cdab94f2d7ba1b352b083f068a262037d053a68113a6.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xAC246218)
MUSASHI_NATIVE_MIPS_WORD(0x3C020007)
MUSASHI_NATIVE_MIPS_WORD(0x3442EFF0)
MUSASHI_NATIVE_MIPS_WORD(0x2483EFF0)
MUSASHI_NATIVE_MIPS_WORD(0x0043102B)
MUSASHI_NATIVE_MIPS_WORD(0x38420001)
MUSASHI_NATIVE_MIPS_WORD(0x00021023)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00821024)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80076218;

s32 func_800351E8(s32 arg0) {
    D_80076218 = arg0;
    return arg0 & -((u32) (arg0 - 0x1010) <= 0x7EFF0U);
}
#endif
