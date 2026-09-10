/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80078E9C;
void func_8014B768(s32 unused, s32 a1) {
    D_80078E9C = D_80078E9C - a1;
    if (*(s16 *)((u8 *)&D_80078E9C + 2) < 0) {
        D_80078E9C = 0;
    }
}
