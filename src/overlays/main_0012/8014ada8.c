/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u32 D_80078E8C;
void func_8014ADA8(s32 unused, s32 a1) {
    u32 v = D_80078E8C + a1;
    D_80078E8C = v;
    if (v > 0x1869F) {
        D_80078E8C = 0x1869F;
    }
}
