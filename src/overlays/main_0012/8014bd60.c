/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80078EB8;
void func_8014BD60(s32 unused, s32 a1) {
    u16 v = D_80078EB8;
    if (v < a1) {
        D_80078EB8 = 0;
    } else {
        D_80078EB8 = v - a1;
    }
}
