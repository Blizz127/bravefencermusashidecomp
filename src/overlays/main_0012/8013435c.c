/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8013435C(s16 *a, s16 *b, s32 extra, s16 *c) {
    s32 lim = -0x2F00;
    if (c[1] < -0xE00) {
        lim = -0x1800;
    }
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + extra < lim;
}
