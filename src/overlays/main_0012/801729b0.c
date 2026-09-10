/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s16 D_80126B34;
extern s16 D_80126B30;
extern s16 D_80126B32;
void func_801729F0();
void func_80174684();
void func_801729B0(s32 a0) {
    D_80126B34 = a0;
    D_80126B30 = 0;
    D_80126B32 = 0;
    func_80174684(func_801729F0);
}
