#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80036F18();                                  /* static */
extern u8 D_800A4F1A;
extern s32 D_800C6D28;

void func_80036EB4(void) {
    if (D_800A4F1A == 0) {
        func_80036F18();
        D_800C6D28 = 0;
    }
}
