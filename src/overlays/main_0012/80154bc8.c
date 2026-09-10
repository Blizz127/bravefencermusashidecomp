/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0xD0]; s32 d0; s16 d4, d6; u8 d8, d9; } T;
void func_80154BC8(T *p, s32 a1, u8 a2) {
    p->d0 = a1;
    p->d6 = 1;
    p->d4 = 1;
    p->d8 = a2;
    p->d9 = a2;
}
