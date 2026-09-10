/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80181080[];
extern s32 D_80078EC8;
void func_80165670(s32 a0, u32 a1) {
    D_80078EC8 = D_80181080[a1 & 0x7F];
}
