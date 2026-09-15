/* Main-exec range [80014028,8001404C) from the SLUS executable.
 * SHA256(span)=5604b09fd49bcce12b06b8274dd6b1222457557b999aa9555101978a0bb041e2.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820002)
MUSASHI_NATIVE_MIPS_WORD(0x94A20002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820008)
MUSASHI_NATIVE_MIPS_WORD(0x94A20004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA482000E)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80014028(s16 *dst, s16 *src) {
    dst[1] = src[0];
    dst[4] = src[1];
    dst[7] = src[2];
}
#endif
