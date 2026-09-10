/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_801151FC;
extern s32 D_80127518;
s32 func_80153BF0(s32 a0) {
    if (a0 == D_801151FC) {
        D_80127518 = 0;
        return 1;
    }
    return 0;
}
