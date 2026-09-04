#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s8 D_801152C0;
extern s16 D_801152C2;
extern s16 D_80127080;

void func_8012A304(s16 arg0, s16 arg1) {
    D_801152C0 = 1;
    D_80127080 = arg0;
    D_801152C2 = arg1;
}
