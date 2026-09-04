#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_800A642C;
extern s32 D_800C7C84;
extern s32 D_800C7C8C;

void func_80046CFC(s32 arg0, s32 arg1, s32 arg2) {
    D_800C7C8C = arg0;
    D_800A642C = arg1;
    D_800C7C84 = arg2;
}
