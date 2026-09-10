/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80181060[];
s32 func_80165658(s32 a0, u32 a1) {
    return D_80181060[a1 & 0x7F];
}
