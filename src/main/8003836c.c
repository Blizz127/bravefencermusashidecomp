/* Exact retail word export for [8003836C,800383A4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000411C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021880)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90229ED3)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400004)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00230821)
MUSASHI_NATIVE_MIPS_WORD(0x90229ED2)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_800B9ED3[];
extern u8 D_800B9ED2[];

/* The shared `i * 4` keeps `i` live in `$v0`, so the scaled index lands
 * in `$v1` instead of folding back into `$v0`; the convergent `rc`
 * keeps the taken block falling through into the shared `jr` with the
 * zero delivered in the `beqz` delay slot. */
s32 func_8003836C(s32 arg0) {
    s32 i = arg0 * 127;
    s32 rc;

    if (D_800B9ED3[i * 4] != 0) {
        rc = D_800B9ED2[i * 4];
    } else {
        rc = 0;
    }
    return rc;
}
#endif
