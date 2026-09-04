#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u32 D_80078980;

s32 func_8005C49C(void) {
    u32 temp_v0;

    temp_v0 = (D_80078980 * 0x41C64E6D) + 0x3039;
    D_80078980 = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}
