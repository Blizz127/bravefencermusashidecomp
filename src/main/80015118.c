/* Main-exec range [80015118,8001513C) from the SLUS executable.
 * SHA256(span)=f88129fef48af4f364691d5ceea2f5c2071cdee94cce56889d7d47c52613bd30.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x94820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFEB)
MUSASHI_NATIVE_MIPS_WORD(0x2C4200D7)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0xA4820000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80015118(u16 *arg0) {
    if ((u32) (*arg0 - 0x15) < 0xD7U) {
        *arg0 = 0x80;
    }
}
#endif
