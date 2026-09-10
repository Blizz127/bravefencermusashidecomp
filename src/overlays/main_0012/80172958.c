/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171D1C();
void func_80171A1C();
void func_80174650();
extern s16 D_80126B30;
extern u8 D_80126B36;
void func_80172958(void *p) {
    if (func_80171D1C(p, &D_80126B30, D_80126B36)) {
        func_80171A1C(p);
        func_80174650(p);
    }
}
