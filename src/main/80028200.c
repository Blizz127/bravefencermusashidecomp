#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80028200(s32 arg0, s32 arg1, s32 arg2, s32 *arg3, s32 arg4) {
    s32 *temp_a0;

    temp_a0 = arg0 + ((arg1 >> arg2) * 4);
    *arg3 = (*temp_a0 & 0xFFFFFF) | arg4;
    *temp_a0 = (s32) arg3 & 0xFFFFFF;
}
