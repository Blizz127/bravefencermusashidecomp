/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_801151E0[];
s32 func_801565C0(void) {
    s32 bits = 0;
    u32 i;
    for (i = 0; i < 3; i++) {
        if (D_801151E0[i] & 1) {
            bits |= 1;
        }
    }
    return bits;
}
