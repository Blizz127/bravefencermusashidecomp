/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_8018394C;
void func_8001534C();
void func_800153CC();
void func_80165E2C(u16 *p) {
    func_8001534C(0, &D_8018394C, 0x80, 0x80, 0, 0);
    func_800153CC(1, p[0], 0xA8, 0x80, 0x40, 0);
}
