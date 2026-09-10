/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80156A14();
typedef struct { u8 pad[0x1A8]; u8 a, b; u8 pad1AA[0x1C0-0x1AA]; u8 c; } T;
void func_80156648(T *p) {
    p->a = 0;
    p->b = 0;
    p->c = 0;
    func_80156A14(p);
}
