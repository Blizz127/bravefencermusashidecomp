/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s16 D_80126B30;
void func_801737E8();
void func_80174684();
void func_801737B8(s32 a0) {
    D_80126B30 = a0;
    func_80174684(func_801737E8);
}
