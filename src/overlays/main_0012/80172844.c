/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171CC4();
void func_80171A1C();
void func_80174650();
extern s16 D_80126B30;
void func_80172844(void *p) {
    if (func_80171CC4(p, &D_80126B30)) {
        func_80171A1C(p);
        func_80174650(p);
    }
}
