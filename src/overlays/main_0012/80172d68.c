/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80126B58;
extern void *D_80127508;
void *func_8014C168();
void func_80172DAC();
void func_80174684();
void func_80172D68(void *p) {
    D_80127508 = func_8014C168(&D_80126B58, p);
    func_80174684(func_80172DAC);
}
