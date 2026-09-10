/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[2]; u16 u2; } T;
void func_80146CB4(T *p) {
    p->u2 = p->u2 - 1;
}
