/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80172760();
void func_80174650();
extern void (*D_80127088)();
extern s32 D_801270BC;
extern s16 D_80126B0C;
void func_801726D0(void) {
    D_80127088 = func_80172760;
    D_801270BC = 0;
    D_80126B0C = 0;
    func_80174650();
}
