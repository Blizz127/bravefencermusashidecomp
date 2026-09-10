#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006CC84;

s32 func_8004359C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8006CC84;
    D_8006CC84 = arg0;
    return temp_v0;
}

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c028007) MUSASHI_NATIVE_MIPS_WORD(0x8c42cc84)
MUSASHI_NATIVE_MIPS_WORD(0x3c018007) MUSASHI_NATIVE_MIPS_WORD(0xac24cc84)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008) MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif
