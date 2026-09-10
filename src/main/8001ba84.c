/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8001BC6C();
extern s32 D_800630E8[];
void func_8001BA84(void) {
    func_8001BC6C(D_800630E8, 0x80);
    func_8001BC6C(D_800630E8 + 2, 0x80);
    func_8001BC6C(D_800630E8 + 4, 0x80);
    func_8001BC6C(D_800630E8 + 6, 0x80);
}
