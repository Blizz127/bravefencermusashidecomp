#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8004689C();                                  /* static */
extern s32 D_800C7C94;
extern s32 D_800C7F00;

void func_80043088(s32 arg0, s32 arg1) {
    D_800C7C94 = arg0;
    D_800C7F00 = arg1;
    func_8004689C();
}
