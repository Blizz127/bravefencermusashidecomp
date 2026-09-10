/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 x, y, z, pad; } S;
typedef struct { u8 pad[0x154]; S s; } T;
void func_8014C860(T *p, S *q) {
    p->s = *q;
    p->s.pad = 1;
}
