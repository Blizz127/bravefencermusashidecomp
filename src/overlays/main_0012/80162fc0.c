/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[4]; s32 a, b, c, d, e, f; } T;
void func_80162FC0(T *p) {
    p->a += p->d;
    p->b += p->e;
    p->c += p->f;
}
