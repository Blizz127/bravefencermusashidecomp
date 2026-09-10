/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_8012697C;
extern s16 D_80126980;
void func_80174F28();
void func_8012A018();
void func_80174E9C(s32 a0) {
    D_8012697C = a0;
    D_80126980 = 0;
    func_8012A018(func_80174F28, 0);
}
