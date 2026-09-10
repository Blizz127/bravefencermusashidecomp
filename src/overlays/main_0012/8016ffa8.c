/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171990();
typedef struct { u8 pad[170]; u16 a; u16 b; } T;
void func_8016FFA8(T *p) {
    p->b |= 64;
    p->a |= 64;
    func_80171990(p);
}
