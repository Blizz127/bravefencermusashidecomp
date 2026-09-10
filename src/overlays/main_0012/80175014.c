/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 a, b, c, d, e, f, g; } S;
typedef struct {
    u8 pad[0x3C]; s32 u3C, u40, u44, u48, u4C, u50, u54;
} T;
s32 func_80175014(T *p, S *tab, s32 idx) {
    S *s = (S *)((u8 *)tab + (s16)idx * 14);
    if (s->g == 0x7FFF) {
        return 1;
    }
    p->u3C = s->a;
    p->u40 = s->b;
    p->u44 = s->c;
    p->u48 = s->d;
    p->u4C = s->e;
    p->u50 = s->f;
    p->u54 = s->g << 5;
    return 0;
}
