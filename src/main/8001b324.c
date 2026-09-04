#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8001B34C();                                  /* static */
extern s32 D_800AE7EC;

void func_8001B324(void) {
    D_800AE7EC = 0;
    func_8001B34C();
}
