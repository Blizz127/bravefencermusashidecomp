/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x1C7]; u8 u1C7; } T;
void func_8014B5C4(T *p, s32 a1, s32 a2) {
    p->u1C7 = a1 | a2;
}
