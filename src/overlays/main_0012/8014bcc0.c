/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80078EB4;
void func_8014BCC0(s32 unused, s32 a1) {
    if (a1 < D_80078EB4) {
        D_80078EB4 = D_80078EB4 - a1;
    } else {
        D_80078EB4 = 1;
    }
}
