/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80147364(s32, s32);                            /* static */
extern s32 D_8012707C;

void func_80147324(s32 arg0) {
    s32 temp_a0;

    temp_a0 = arg0 & 0xFFFF;
    if (temp_a0 == D_8012707C) {
        D_8012707C = 0;
        return;
    }
    func_80147364(temp_a0, 0);
}
