/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_8016F1AC();                                /* static */
extern s32 D_80078E98;
extern s16 D_80078E9A;

void func_8014B504(u16 *arg0) {
    s32 temp_v1;
    u16 temp_a0;

    if (func_8016F1AC() == 0) {
        temp_a0 = *arg0;
        if ((temp_a0 != 0x1E) && (temp_a0 != 0x1A) && (D_80078E9A & 0x8000)) {
            temp_v1 = D_80078E98 + 0x1555;
            D_80078E98 = temp_v1;
            if ((temp_v1 & 0x7FFF0000) > 0x257F6A) {
                D_80078E98 = 0;
            }
        }
    }
}
