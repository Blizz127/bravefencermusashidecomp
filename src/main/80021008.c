#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80028620(s32, s32);                            /* static */

void func_80021008(s32 arg0) {
    func_80028620(0, arg0);
    func_80028620(1, arg0 + 0x10);
    func_80028620(2, arg0 + 0x20);
}
