/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Inner { u8 pad[0x12]; s16 u12; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
s32 func_80148C20(T *p, s32 a1) {
    p->inner->u12 = a1;
    return 1;
}
