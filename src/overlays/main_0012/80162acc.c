/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad; u8 u1; } T;
void func_80162ACC(T *p) {
    p->u1 = p->u1 + 1;
}
