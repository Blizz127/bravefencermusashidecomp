#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80029344();                                  /* static */
extern s32 D_80078E90;

void func_80029664(void) {
    D_80078E90 = 0x528;
    func_80029344();
}
