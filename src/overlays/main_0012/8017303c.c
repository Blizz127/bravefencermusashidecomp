/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80127508;
extern s16 D_80126B30;
void func_80173078();
void func_80174684();
void func_8017303C(s32 a0) {
    D_80127508 = a0;
    D_80126B30 = 1;
    func_80174684(func_80173078);
}
