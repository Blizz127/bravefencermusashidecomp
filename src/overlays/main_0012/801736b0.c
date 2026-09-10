/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80126B58;
extern void *D_80127508;
void *func_8014C118();
void func_801736FC();
void func_80174684();
void func_801736B0(void *p, s32 a1) {
    D_80127508 = func_8014C118(&D_80126B58, p, (s16)a1);
    func_80174684(func_801736FC);
}
