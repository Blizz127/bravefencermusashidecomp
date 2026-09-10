/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80078E9C;
extern s32 D_80078ED0;
void func_8014B6F0(s32 unused, s32 a1) {
    D_80078E9C = D_80078E9C + a1;
    if (*(s16 *)((u8 *)&D_80078E9C + 2) >= 0xA1) {
        D_80078E9C = 0xA00000;
    }
    D_80078ED0 = D_80078ED0 + a1;
    if (*(s16 *)((u8 *)&D_80078ED0 + 2) >= 0xA1) {
        D_80078ED0 = 0xA00000;
    }
}
