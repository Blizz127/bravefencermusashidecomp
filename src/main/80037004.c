/* Exact retail word export for [80037004,80037028); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020040)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xa0206251)
MUSASHI_NATIVE_MIPS_WORD(0x2442fff0)
MUSASHI_NATIVE_MIPS_WORD(0x0441fffb)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_80076251[];

/* Byte table zeroed top-down in `0x10` steps; the `u8` element type
 * keeps the index unscaled so the address folds to `lui` + `addu`
 * recomputed each iteration. Identical twin: func_80037334. */
void func_80037004(void) {
    s32 i = 0x40;

    do {
        D_80076251[i] = 0;
        i -= 0x10;
    } while (i >= 0);
}
#endif
