/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x18]; u16 u3C, u3E, u40, u42;
} T;
void func_80151184(T *p, s32 a1, s32 a2) {
    Inner *in = p->inner;
    p->u3E = a1;
    p->u40 = a2;
    p->u42 = in->u12;
    p->u3C |= 1;
}
