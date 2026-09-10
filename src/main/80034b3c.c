#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8007620C;

s32 func_80034B3C(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_8006AEF8 != D_8006AEFC) {
        if (D_8007620C & 0x80) {
            return 2;
        }
        var_v0 = 1;
        if (D_8007620C & 0x20) {
            return 4;
        }
        /* Duplicate return node #6. Try simplifying control flow for better match */
        return var_v0;
    }
    D_8007620C = 0;
    return var_v0;
}
