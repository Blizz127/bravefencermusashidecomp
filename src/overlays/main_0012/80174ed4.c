/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u16 D_80126980;

s16 func_80174ED4(void) {
    return (s16) (D_80126980 & 0x8000);
}
