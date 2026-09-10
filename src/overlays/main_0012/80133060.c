/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801330E0();
typedef struct { s32 x, y, z; } V;
void func_80133060(s16 *p, V *q, s32 a2) {
    s16 tmp[3];
    tmp[0] = p[1];
    tmp[1] = p[3];
    tmp[2] = p[5];
    func_801330E0(tmp, tmp, (s16)a2);
    q->x = tmp[0] << 16;
    q->y = tmp[1] << 16;
    q->z = tmp[2] << 16;
}
