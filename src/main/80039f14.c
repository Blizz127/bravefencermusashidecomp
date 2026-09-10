/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x20]; u8 u20, u21, u22; } S;
void func_80039F14(S *p, s32 idx, s32 a2) {
    p = (S *)((u8 *)p + (s16)idx * 26);
    p->u20 = a2;
    p->u22 = a2 + 1;
    p->u21 |= 2;
}
