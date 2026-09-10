/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80078EB8;
extern u16 D_80078EB6;
void func_8014BD98(s32 unused, u16 a1) {
    D_80078EB8 = a1;
    if (a1 > D_80078EB6) {
        D_80078EB8 = D_80078EB6;
    }
}
