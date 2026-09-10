/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_800747C8;
extern u8 D_800B9A64;
extern s32 D_800747C0;
extern u8 D_800747C4;
extern u8 D_800747C5;
void func_80019064(s32 a0) {
    if (D_800747C8 == 0 && D_800B9A64 == 0) {
        D_800747C0 = a0;
        D_800747C4 = 0xFF;
        D_800747C5 = 0;
    }
}
