/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149374();
void func_800D1FC8();
typedef struct { s32 a, b, c, d; u8 pad[0x24]; void *p34; } T;
void func_8016DBD8(T *p) {
    p->b = 0;
    p->c = 0;
    p->d = 0;
    func_80149374(p->p34, &p->b);
    func_800D1FC8(p, 5);
}
