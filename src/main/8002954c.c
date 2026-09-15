/* Main-exec range [8002954C,8002955C) from the SLUS executable.
 * SHA256(span)=971457110bdbde5fb38aaa2bed77d77a69eeb878e0f613b18d7638add019a2a4.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC248E84)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078E84;

void func_8002954C(s32 arg0) {
    D_80078E84 = arg0;
}
#endif
