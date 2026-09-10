/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80173A60();
extern s32 D_8012750C;
void func_80173A28(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    func_80173A60(a0, a1, a2, a3, a4);
    D_8012750C = a5;
}
