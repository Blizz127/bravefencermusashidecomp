#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80029178();                               /* static */
s32 func_8002A2B0();                                /* static */
s32 func_8002A9DC();                                /* static */

s32 func_80029DB4(void) {
    s32 temp_s0;
    s32 var_s1;

    var_s1 = 0x7D;
    if (func_80029178(0x81) & 0xFF) {
        var_s1 = 0x96;
    }
    temp_s0 = func_8002A9DC();
    return ((temp_s0 + func_8002A2B0()) * var_s1) / 100;
}
