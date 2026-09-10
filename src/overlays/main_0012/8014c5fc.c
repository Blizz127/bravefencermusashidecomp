/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80047D3C();
s32 func_8004CFEC();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
} T;
typedef struct { s16 x, y, z; } V;
s32 func_8014C5FC(T *p, T *q, V *r) {
    s32 dx = (s16)(q->uE + r->z - p->uE);
    s32 dy = (s16)(q->u6 + r->x - p->u6);
    s32 mag = func_80047D3C(dx * dx + dy * dy);
    return func_8004CFEC(q->uA + r->y - p->uA, (s16)mag) & 0xFFF;
}
