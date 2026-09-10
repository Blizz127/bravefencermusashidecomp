/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x1BE]; u8 v; } T;
void func_8014A71C(T *p) {
    if (p->v) {
        p->v = p->v - 1;
    }
}
