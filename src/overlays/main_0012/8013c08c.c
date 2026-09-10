/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8013C0F8();
typedef struct { u8 pad[8]; void *a; u8 *b; } T;
void func_8013C08C(T *p, u8 *q) {
    u8 *tmp = q;
    p->a = q;
    p->b = tmp + 0x14;
    func_8013C0F8(q);
}
