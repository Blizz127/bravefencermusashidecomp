/* Main-exec range [8002A27C,8002A28C) from the SLUS executable.
 * SHA256(span)=8c69728ba4c6865dabea5ac5e584075f28b40e565fdd4e920585c8edb89d883c.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428EE8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078EE8;

s32 func_8002A27C(void) {
    return D_80078EE8;
}
#endif
