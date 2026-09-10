/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_801152BC;
s32 func_801612B8();
void func_80161374();
void func_80161278(void *p) {
    D_801152BC = 0;
    func_80161374(p, func_801612B8(p, 1));
}
