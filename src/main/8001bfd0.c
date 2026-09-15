/* Main-exec range [8001BFD0,8001BFE8) from the SLUS executable.
 * SHA256(span)=66dbd9d6bd6dc546cf6dae2e7da9e108b4c378c6fb8fd91da0656f5bab63f339.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xAC202B70)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xAC20A0FC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800A2B70;
extern s32 D_800BA0FC;

void func_8001BFD0(void) {
    D_800A2B70 = 0;
    D_800BA0FC = 0;
}
#endif
