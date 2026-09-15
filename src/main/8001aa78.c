/* Main-exec range [8001AA78,8001AA88) from the SLUS executable.
 * SHA256(span)=9f9cced133e55e3e0938c81f3cf519f03521b4c9e83cb717bb7e07b59896b0e7.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800B)
MUSASHI_NATIVE_MIPS_WORD(0x8C42E708)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800AE708;

s32 func_8001AA78(void) {
    return D_800AE708;
}
#endif
