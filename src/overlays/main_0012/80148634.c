/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0xAA]; u16 uAA, uAC, uAE; } T;
void func_80148634(T *p) {
    p->uAA = 0;
    p->uAC = 0;
    p->uAE = 0x8080;
}
