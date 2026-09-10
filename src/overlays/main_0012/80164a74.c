/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80148534();
void func_80015954();
void func_80149374();
typedef struct { u8 pad[0x4C]; void *u4C; } T;
void func_80164A74(T *p) {
    s16 a[4];
    s16 b[4];
    void *q = p->u4C;
    func_80148534(a, b);
    func_80015954(a, (u8 *)p + 4);
    func_80149374(q, (u8 *)p + 4);
}
