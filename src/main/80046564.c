/* Main-exec range [80046564,8004657C) from the SLUS executable.
 * Word export for the native seam; the body below is a verified C match. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x2463CFD0)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0xAC640000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s and verified byte-exact against retail by
 * tools/match_function.py (6/6 words). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original declaration.
 *
 * The volatile local pointer is load-bearing: it stops GCC sinking the
 * store into the `jr` delay slot and makes the load and store share one
 * base register ($v1), which is retail's shape. A plain global reference
 * gives the two-base form seen in func_8004654C and does not match. */

extern s32 D_8006CFD0;

s32 func_80046564(s32 arg0) {
    volatile s32 *p = &D_8006CFD0;
    s32 old = *p;

    *p = arg0;
    return old;
}
#endif
