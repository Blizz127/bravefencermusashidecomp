#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern s8 D_800A4F1A;

void func_80036D24(void) {
    D_80078F10 = 0;
    if (D_8006AEE8 < 2) {
        D_8006AEE8 = 0;
        D_800A4F1A = 0;
    }
}
