/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
typedef struct {
    u8 pad[8];
    s32 a, b, c, d;
    S s;
    S t;
    s16 u, v, w;
    s16 x, y, z;
} T;
void func_8012A094(T *p) {
    p->a = p->b;
    p->c = p->d;
    p->s = p->t;
    p->u = p->x;
    p->v = p->y;
    p->w = p->z;
}
