/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
typedef struct { u16 x, y, z; } H;
typedef struct {
    u8 pad[6];
    u16 a;
    u8 pad8[2];
    u16 b;
    u8 padC[2];
    u16 c;
    u8 padE[0x88-0x10];
    S s88;
    S s90;
} T;
void func_80172358(T *p, H *q) {
    p->a = q->x;
    p->b = q->y;
    p->c = q->z;
    p->s90 = *(S *)q;
    p->s88 = p->s90;
}
