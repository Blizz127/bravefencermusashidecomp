/* Main-exec range [8003FE18,8003FE3C) from the SLUS executable.
 * SHA256(span)=6e0cb340c3f01d857ecc71d3de8b3cec6e0a792a6055b6338a81c98db6490265.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x240600CA)
MUSASHI_NATIVE_MIPS_WORD(0x0C00EFA6)
MUSASHI_NATIVE_MIPS_WORD(0x240700CB)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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
void func_8003BE98();
void func_8003FE18(void *a, void *b) { func_8003BE98(a, b, 0xCA, 0xCB); }
#endif
