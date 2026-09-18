/* Exact retail word export for [80029178,800291A0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x000410C2)
MUSASHI_NATIVE_MIPS_WORD(0x30840007)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x9022E648)
MUSASHI_NATIVE_MIPS_WORD(0x00831804)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x0002102B)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_800AE648[];

/* Staged into explicit temps: the single-expression form lets the
 * combiner rewrite `(x & (1 << n)) != 0` as `(x >> n) & 1`, and the
 * scheduler folds the table load ahead of the mask setup. Staging
 * pins index, mask-bit, constant, load, shifted mask, test. */
s32 func_80029178(u32 arg0) {
    u32 i = arg0 >> 3;
    u32 a = arg0 & 7;
    u32 one = 1;
    u32 v = D_800AE648[i];
    u32 m = one << a;

    return (v & m) != 0;
}
#endif
