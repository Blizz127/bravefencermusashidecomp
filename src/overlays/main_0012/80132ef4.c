#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8012913C(s32);                             /* static */
void func_80129350(s32, s32);                          /* static */

s32 func_80132EF4(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = func_8012913C(arg1 & 0xFFFF);
    if (temp_v0 != 0) {
        func_80129350(temp_v0, arg0);
    }
    return temp_v0;
}
