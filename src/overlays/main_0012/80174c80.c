/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80174CB0();
typedef struct { u8 pad[0xA0]; u16 f; } T;
void func_80174C80(T *p) {
    u16 v = (p->f - 0x16) & 0xFFF;
    p->f = v;
    func_80174CB0(p, v);
}
