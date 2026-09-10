/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 *D_8006B54C;
extern s16 D_8006B100;
extern s16 D_8006B102;
void func_8003D3F8(s32 a0, s32 a1) {
    s16 *g = (s16 *)(D_8006B54C + 0x184);
    g[0] = a0;
    g[1] = a1;
    D_8006B100 = a0;
    D_8006B102 = a1;
}
