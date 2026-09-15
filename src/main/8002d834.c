/* Main-exec range [8002D834,8002D844) from the SLUS executable.
 * SHA256(span)=119b0b426591a4a177d5d37e951a87f3cbe6232bcdcd8d6215ce4c71d8de94e9.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA420A990)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u16 D_8006A990;

void func_8002D834(void) {
    D_8006A990 = 0;
}
#endif
