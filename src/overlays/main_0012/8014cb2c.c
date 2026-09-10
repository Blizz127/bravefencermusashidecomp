/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80126D1F;
s32 func_8014CB2C(void) {
    s32 v = D_80126D1F;
    if (v & 0x80) {
        v = (v & 0x7F) | 0x80000000;
    }
    return v;
}
