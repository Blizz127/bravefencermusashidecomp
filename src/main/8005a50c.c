/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8005AB58();
s32 func_8005AC24();
typedef struct { s16 x, y, w, h; } RECT;
typedef struct { u8 pad[3]; u8 unk3; s32 a, b; } T;
void func_8005A50C(T *p, RECT *r) {
    p->unk3 = 2;
    p->a = func_8005AB58(r->x, r->y);
    p->b = func_8005AC24((s16)(r->x + r->w - 1), (s16)(r->y + r->h - 1));
}
