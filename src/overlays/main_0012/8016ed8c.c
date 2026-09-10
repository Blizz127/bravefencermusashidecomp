/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016EDEC();
extern s32 D_80126D70;
void func_8016ED8C(void *a0, void *a1, s32 a2) {
    func_8016EDEC(a0, a1, a2);
    D_80126D70 = a2;
}
