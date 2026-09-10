/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x50]; u8 a, b, c; u8 pad53[0xF]; u16 u62; } T;
void func_80165124(T *p) {
    p->a = p->u62;
    p->b = p->u62;
    p->c = p->u62;
}
