/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u16 D_8006A990;
extern u16 D_800A4E8E;

u16 func_8002D80C(void) {
    if (D_800A4E8E & 1) {
        return D_8006A990;
    }
    return 0;
}
