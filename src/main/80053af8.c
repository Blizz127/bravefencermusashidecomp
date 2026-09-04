#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800491FC(s32, s32, s32);                     /* static */

void func_80053AF8(s32 arg0, s32 arg1, s32 arg2) {
    func_800491FC(arg0 >> 4, arg1 >> 4, arg2 >> 4);
}
