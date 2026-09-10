#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80029504();                                /* static */

s32 func_8002AA3C(void) {
    s32 temp_v0;

    temp_v0 = func_80029504();
    if (temp_v0 >= 0x4B0) {
        return 0x63;
    }
    if (temp_v0 >= 0x384) {
        return 0x1B;
    }
    if (temp_v0 >= 0x258) {
        return 0x16;
    }
    if (temp_v0 >= 0xC8) {
        return 0x10;
    }
    return (temp_v0 >= 0xA) * 8;
}
