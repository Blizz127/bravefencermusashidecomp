#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8002C8BC();                                  /* static */
extern s16 D_800A46CC;

void func_8002FAE0(void) {
    D_800A46CC = 0;
    func_8002C8BC();
}
