#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8014B084();                                  /* static */
extern u16 D_80078E92;

void func_8014B034(s32 arg0) {
    s16 temp_v1;

    temp_v1 = D_80078E92 + arg0;
    D_80078E92 = (u16) temp_v1;
    if (temp_v1 >= 0x5A0) {
        D_80078E92 = temp_v1 - 0x5A0;
        func_8014B084();
    }
}
