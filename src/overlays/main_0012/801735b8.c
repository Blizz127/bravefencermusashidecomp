/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A1C();
typedef struct { u8 pad[170]; u16 a; u16 b; } T;
void func_801735B8(T *p) {
    p->b |= 64;
    p->a |= 64;
    func_80171A1C(p);
}
