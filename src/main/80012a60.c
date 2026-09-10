#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s16 func_80012AB0(s16, s16);                        /* static */

s16 func_80012A60(s16 arg0, s16 arg1) {
    s16 var_v1;

    var_v1 = func_80012AB0(arg0, arg1);
    if (var_v1 >= 0x800) {
        var_v1 = 0xFFF - var_v1;
    }
    return var_v1;
}
