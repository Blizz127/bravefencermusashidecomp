/* Main-exec range [80043430,80043440) from the SLUS executable.
 * SHA256(span)=86e0e9c8b65dd7eb2a2bf15dd0a8fd58638ebf1573fa14794c2cc168c70e36da.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x9042CCA5)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006CCA5;

u8 func_80043430(void) {
    return D_8006CCA5;
}
#endif
