#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80031D70();                                  /* static */
extern s16 D_800A4EF0;

void func_8002F620(void) {
    D_800A4EF0 = 0;
    func_80031D70();
}
