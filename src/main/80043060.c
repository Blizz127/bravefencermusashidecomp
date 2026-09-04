#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006CBE8;

s32 func_80043060(s32 arg0) {
    s32 temp_v0;

    temp_v0 = D_8006CBE8;
    D_8006CBE8 = arg0;
    return temp_v0;
}
