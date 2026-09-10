/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x24]; s32 u24, u28, u2C; } T;
void func_80146DE8(T *p, s32 a1, s32 a2, s32 a3) {
    p->u24 = a1;
    p->u28 = a2;
    p->u2C = a3;
}
