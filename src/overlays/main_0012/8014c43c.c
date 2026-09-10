/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80156370();
void func_8014C4AC();
void func_8014C43C(void *a0, void *a1, u32 a2, void *a3, s32 a4) {
    u32 v = func_80156370((u16)a2);
    func_8014C4AC(a1, a2, (u16)v, a3, (s16)a4);
}
