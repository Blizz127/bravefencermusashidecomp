/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80165658();
extern u8 D_80078EC1;
extern u16 D_80078EB8;
s32 func_80165624(s32 a0) {
    u32 v = func_80165658(a0, D_80078EC1 & 0x7F) & 0x7F;
    return D_80078EB8 < v;
}
