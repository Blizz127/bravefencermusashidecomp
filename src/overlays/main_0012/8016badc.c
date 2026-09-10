/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80146A6C(s32, s32, s32, s16, s32, s32, s32);     /* static */

void func_8016BADC(s32 arg0, s16 arg1, s32 arg2) {
    func_80146A6C(0x22, arg0, 0, arg1, 0, 0, arg2);
    func_80146A6C(0x22, arg0, 0, arg1, 0, 1, arg2);
    func_80146A6C(0x22, arg0, 0, arg1, 0, 2, arg2);
    func_80146A6C(0x24, arg0, 0, arg1, 0, 0, 0);
}
