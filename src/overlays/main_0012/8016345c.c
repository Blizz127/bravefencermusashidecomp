#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80156370(s32);                             /* static */
void func_80163534(s32, s32, s32, s32, s32, s32);        /* static */

void func_8016345C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_s2;

    temp_s2 = arg1 & 0xFFFF;
    func_80163534(arg0, temp_s2, func_80156370(temp_s2) & 0xFFFF, arg2, arg3 & 0xFFFF, arg4);
}
