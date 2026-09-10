/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800D5DA8;
void func_801719A4();
void func_8014706C();
void func_80154274();
void func_8016BADC();
void func_80171990();
void func_801708B0();
void func_8017084C(void *p) {
    func_801719A4(p, 1);
    func_8014706C(p);
    func_80154274(p, &D_800D5DA8);
    func_8016BADC(p, -0x40, 0x40);
    func_80171990(p);
    func_801708B0(p);
}
