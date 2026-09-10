/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x214]; u8 a, b, c; } T;
void func_80171A1C(T *p) {
    p->b = 0;
    p->c = 0;
    p->a++;
}
