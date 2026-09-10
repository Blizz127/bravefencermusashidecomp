/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_800291A0(s32, s32);                            /* extern */

void func_8014BF18(s32 arg0) {
    s32 var_a1;

    var_a1 = arg0;
    if (var_a1 < 0) {
        var_a1 = 0;
    }
    func_800291A0(0xCF, var_a1 & 0xFF);
}
