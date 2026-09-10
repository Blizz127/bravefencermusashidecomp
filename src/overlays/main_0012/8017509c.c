/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 a, b, c, d, e, f, g; } S;
s32 func_8017509C(S *tab, s32 idx, s16 *xy, s16 *uv) {
    S *s = (S *)((u8 *)tab + (s16)idx * 14);
    if (s->g == 0x7FFF) {
        return 1;
    }
    xy[0] = s->a;
    xy[1] = s->b;
    xy[2] = s->c;
    uv[0] = s->d;
    uv[1] = s->e;
    uv[2] = s->f;
    return 0;
}
