#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8001ABBC(s32, s32, void *, s32, s32);               /* extern */
extern s32 D_80182D1C;
extern s32 *D_800AECB8;

void func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_80182D1C, 0);
}
