/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[6]; u16 u6; u8 pad8[2]; u16 uA; } T;
typedef struct { u8 pad[8]; u16 u8, uA, uC; } D;
void func_8016B964(T *p, D *d) {
    d->u8 = p->u6;
    d->uA = p->uA;
    d->uC = 3;
}
