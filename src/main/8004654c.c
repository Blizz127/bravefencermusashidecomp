#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006CF9C;

s32 func_8004654C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8006CF9C;
    D_8006CF9C = arg0;
    return temp_v0;
}
