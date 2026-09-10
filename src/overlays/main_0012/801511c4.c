/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x3E]; u16 a, b, c; u8 pad44[0xAC]; u16 d, e, f; } T;
void func_801511C4(T *p) {
    p->d = p->a;
    p->e = p->b;
    p->f = p->c;
}
