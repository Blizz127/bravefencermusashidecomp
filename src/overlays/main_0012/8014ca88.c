#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80147364(s32, s32);                            /* static */
s32 func_8014CAE4();                                /* static */
extern s32 D_8012707C;

s32 func_8014CA88(void) {
    s32 temp_a0;
    s32 var_v0;

    temp_a0 = func_8014CAE4() & 0xFFFF;
    var_v0 = 1;
    if (temp_a0 != 0) {
        if (temp_a0 == D_8012707C) {
            D_8012707C = 0;
            return 0;
        }
        func_80147364(temp_a0, 0);
        var_v0 = 0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
