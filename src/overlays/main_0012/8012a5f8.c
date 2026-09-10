#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012A62C(s32);                               /* static */

void func_8012A5F8(s32 (*arg0)(), s32 arg1) {
    func_8012A62C(arg1 & 0xFF);
    arg0();
}
