/* Main-exec range [80058E24,80058E38) from the SLUS executable.
 * SHA256(span)=78d3cb56016e3c3c7958742801a8e44a995a9a017c25c21a61346c13c34faddb.
 * Word export for the native seam; the body below is kept
 * byte-identical (wrap only, no rewrite). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x2402007C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820007)
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
void func_80058E24(u8 *p) {
    p[3] = 3;
    p[7] = 124;
}
#endif
