#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80074794;
extern s32 D_80074798;

void func_800120DC(u16 *arg0, u16 *arg1) {
    *arg0 = D_80074794;
    *arg1 = D_80074798;
}
