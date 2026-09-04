#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_8002A9A8();                                /* static */
s32 func_8002A9B8();                                /* static */

s32 func_8002A92C(void) {
    s32 temp_s0;

    temp_s0 = func_8002A9B8();
    return func_8002A9A8() >= temp_s0;
}
