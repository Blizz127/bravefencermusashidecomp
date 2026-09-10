#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_801377B4(s32, s32, s32);                       /* static */
s32 func_801399A8();                                /* static */

s32 func_8013767C(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_801399A8();
    if (temp_v0 != 0) {
        func_801377B4(arg0, 0, temp_v0);
    }
    return temp_v0;
}
