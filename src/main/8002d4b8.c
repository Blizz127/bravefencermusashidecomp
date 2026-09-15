/* Main-exec range [8002D4B8,8002D4C8) from the SLUS executable.
 * SHA256(span)=2a6ef47b0368d20bb70064b9d79bee097fbd35dddb41da6cd43e71a93bb8f2c2.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800A)
MUSASHI_NATIVE_MIPS_WORD(0x904246BA)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_800A46BA;

u8 func_8002D4B8(void) {
    return D_800A46BA;
}
#endif
