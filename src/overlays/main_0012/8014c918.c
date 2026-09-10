/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_801151F0[];
s32 func_8014C918(s32 unused, s32 a1) {
    u8 i;
    if (a1 == 0x18) {
        return 8;
    }
    for (i = 0; i < 8; i++) {
        if (D_801151F0[i] == a1) {
            return i;
        }
    }
    return 0;
}
