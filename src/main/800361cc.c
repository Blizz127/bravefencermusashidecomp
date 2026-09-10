#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006AEF0;
s32 func_800435B4();                                /* static */
extern u8 D_80076110;

void func_800361CC(void) {
    if (D_80076110 == 0) {
        D_8006AEF0 = func_800435B4();
    } else {
        func_800435B4();
    }
    D_80076110 = 1;
}
