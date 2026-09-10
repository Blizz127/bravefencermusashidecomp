/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8015773C();
typedef struct { u8 pad[0x1AA]; u8 f; } T;
void func_8015771C(T *p) {
    p->f = 0;
    func_8015773C(p);
}
