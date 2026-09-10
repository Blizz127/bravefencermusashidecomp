#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80053AF8(s16, s16, s16);                     /* static */
extern s16 D_800AE7E0;
extern s16 D_800AE7E2;
extern s16 D_800AE7E4;

void func_80021120(s32 *arg0) {
    func_80053AF8(D_800AE7E0, D_800AE7E2, D_800AE7E4);
    *arg0 += 1;
}
