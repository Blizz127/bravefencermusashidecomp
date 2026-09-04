#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80076218;

s32 func_800351E8(s32 arg0) {
    D_80076218 = arg0;
    return arg0 & -((u32) (arg0 - 0x1010) <= 0x7EFF0U);
}
