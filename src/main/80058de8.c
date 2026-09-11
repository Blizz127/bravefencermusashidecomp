/* Main-exec range [80058DE8,80058DFC) from the SLUS executable.
 * SHA256(span)=baf4b857788c5e448d6537622f5554becdd1a47969d8e97e168e8444f1864c06.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020008)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x24020038)
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
void func_80058DE8(u8 *p) {
    p[3] = 8;
    p[7] = 56;
}
#endif
