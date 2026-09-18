/* Exact retail word export for [8001B788,8001B7C4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00042400)
MUSASHI_NATIVE_MIPS_WORD(0x00042403)
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018006)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x84223138)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x000210C0)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800B)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22E830)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

typedef struct { s16 v; u8 pad[4]; } T_8001B788;
extern T_8001B788 D_80063138[];
extern u8 D_800AE830[];

/* Same struct-stride family as func_80014BFC: the 6-byte stride with
 * a halfword member makes the compiler emit the `* 6` chain plus a
 * folding address, and the final table is byte-indexed (no scaling). */
s32 func_8001B788(s32 arg0) {
    s32 k = D_80063138[(s16)arg0].v << 3;

    return *(s32 *)&D_800AE830[k];
}
#endif
