/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80183B94;
void func_8001534C();
void func_800153CC();
void func_80178438(u16 *p) {
    func_8001534C(2, &D_80183B94, 0x80, 0x88, 0, 0);
    func_800153CC(3, p[0], 0xA8, 0x88, 0x40, 0);
}
