/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80126B5E, D_80126B62, D_80126B66;
extern u16 D_80126940, D_80126942, D_80126944;
void func_8012A048(u8 *p, void *a1, u8 a2) {
    *(void **)p = a1;
    p[4] = a2;
    *(s32 *)(p + 0x9C) = 0;
    *(s16 *)(p + 0xA0) = 0;
    *(s16 *)(p + 0xA2) = 0;
    D_80126940 = D_80126B5E;
    D_80126942 = D_80126B62;
    D_80126944 = D_80126B66;
}
