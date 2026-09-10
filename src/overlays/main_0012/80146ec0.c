/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80015954();
void func_80149374();
void func_80146F58();
typedef struct { s16 a, x, b, y, c, z; } S;
void func_80146EC0(void *p, S *q, void *r, void *s) {
    s16 tmp[4];
    func_80015954(r, q);
    func_80149374(p, q);
    func_80146F58(s, tmp);
    q->x += tmp[0];
    q->y += tmp[1];
    q->z += tmp[2];
}
