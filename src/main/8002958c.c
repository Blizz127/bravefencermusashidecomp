/* Main-exec range [8002958C,8002959C) from the SLUS executable.
 * SHA256(span)=6f3b2b2920a8a216bae3c10a109acaeb692b31ec3b6886345e9033bc88f9ea00.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC248E88)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078E88;

void func_8002958C(s32 arg0) {
    D_80078E88 = arg0;
}
#endif
