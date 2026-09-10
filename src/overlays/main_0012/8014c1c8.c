/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80133784();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
} Q;
typedef struct { s16 x, y, z; } V;
void func_8014C1C8(Q *p, Q *q, V *r) {
    s16 a[4];
    s16 b[4];
    a[0] = p->u6;
    a[1] = p->uA;
    a[2] = p->uE;
    b[0] = q->u6 + r->x;
    b[1] = q->uA + r->y;
    b[2] = q->uE + r->z;
    if (func_80133784(1, a, b)) {
        q->u6 = b[0];
        q->uA = b[1];
        q->uE = b[2];
    }
}
