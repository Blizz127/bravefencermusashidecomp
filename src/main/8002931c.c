#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80029344();                                  /* static */
extern s32 D_80078E90;

void func_8002931C(s32 arg0) {
    D_80078E90 = arg0;
    func_80029344();
}
