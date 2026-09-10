/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80029178();
void func_80029124();
void func_800D1734();
extern s32 D_800AE6B0;
extern s32 D_800AE6A8;
extern s32 D_80180EBC;
void func_80161D88(void) {
    if (D_800AE6B0 & 0x80FFFFFF) {
        return;
    }
    if (D_800AE6A8 & 0x80FFFFFF) {
        return;
    }
    if (func_80029178(0x141) & 0xFF) {
        func_80029124(0x141, 0);
        func_80029124(0x95, 1);
        func_800D1734(&D_80180EBC);
    }
}
