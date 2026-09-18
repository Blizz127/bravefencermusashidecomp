/* Exact retail word export [80046994,800469A8); verified against pinned EXE and asm. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03800C)
MUSASHI_NATIVE_MIPS_WORD(0x24639B54)
MUSASHI_NATIVE_MIPS_WORD(0x8C620000)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC640000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800B9B54;

/* Swap-and-return through a held pointer: the address materializes
 * once (`lui` + `addiu`) with zero-offset accesses. Same shape as
 * func_8004359C's family; whether the `addiu` survives or folds into
 * the memops is symbol-dependent (compare func_80046564, still
 * open, whose identical source folds). */
s32 func_80046994(s32 arg0) {
    s32 *p = &D_800B9B54;
    s32 old = *p;

    *p = arg0;
    return old;
}
#endif
