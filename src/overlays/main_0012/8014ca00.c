/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Q { u8 pad[0x2C]; s16 u2C; } Q;
typedef struct { u8 pad[0x78]; Q *u78; } T;
s32 func_8014CA00(T *p) {
    return p->u78->u2C;
}
