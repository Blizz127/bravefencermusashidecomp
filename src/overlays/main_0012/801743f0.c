#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80171A1C(s32);                               /* static */
s32 func_80172658();                                /* static */
void func_80174650(s32);                               /* static */

void func_801743F0(s32 arg0) {
    if (func_80172658() != 0) {
        func_80171A1C(arg0);
        func_80174650(arg0);
    }
}
