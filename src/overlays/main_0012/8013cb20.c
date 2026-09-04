#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_801841BC;
extern s32 D_801841C0;
extern s32 D_801841E8;
extern s32 D_801841EC;

void func_8013CB20(void) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = D_801841C0;
    temp_a0 = D_801841BC;
    D_801841C0 = 1;
    D_801841BC = 0;
    D_801841E8 = temp_v0;
    D_801841EC = temp_a0;
}
