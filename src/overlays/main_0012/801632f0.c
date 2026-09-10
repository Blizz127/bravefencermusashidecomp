/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80115200[];
s32 func_801632F0(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_80115200[i] != 0) {
            return D_80115200[i];
        }
    }
    return 0;
}
