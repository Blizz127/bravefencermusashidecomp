/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[6]; u16 a; u8 pad8[2]; u16 b; u8 padC[2]; u16 c;
    u8 pad10[2]; u16 d; u8 pad14[2]; u16 e; u8 pad18[2]; u16 f; } T;
void func_8016BF34(T *p) {
    p->d = p->a;
    p->e = p->b;
    p->f = p->c;
}
