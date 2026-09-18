/* Exact retail word export for [8002C8BC,8002C8F4); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x2404ffff)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0xa4245328)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0xa424532a)
MUSASHI_NATIVE_MIPS_WORD(0x24630004)
MUSASHI_NATIVE_MIPS_WORD(0x2c6201e4)
MUSASHI_NATIVE_MIPS_WORD(0x1440fff7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_800C5328[];
extern u8 D_800C532A[];

/* Dual halfword-table fill: the `-1` lives in `$a0` across the loop
 * (no call to clobber it) while the unsigned byte index walks in
 * `$v1`; both base addresses recompute each iteration. */
void func_8002C8BC(void) {
    s32 v = -1;
    u32 i = 0;

    do {
        *(s16 *)(D_800C5328 + i) = v;
        *(s16 *)(D_800C532A + i) = v;
        i += 4;
    } while (i < 0x1E4);
}
#endif
