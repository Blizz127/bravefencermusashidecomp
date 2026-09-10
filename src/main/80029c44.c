/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_80029CD4(s16);                             /* static */
s32 func_80029DB4();                                /* static */
s32 func_80029E30();                                /* static */

s32 func_80029C44(s16 arg0, s16 arg1) {
    s32 temp_s1;
    s32 temp_s3;

    temp_s1 = func_80029DB4();
    temp_s3 = func_80029E30();
    return ((temp_s1 + temp_s3) * (arg0 + func_80029CD4(arg1))) / 100;
}
