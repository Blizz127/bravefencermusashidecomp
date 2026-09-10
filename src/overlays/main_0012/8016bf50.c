/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80149350();
void func_80015954();
typedef struct {
    u8 pad[0x12]; s16 u12;
    u8 pad14[2]; s16 u16;
    u8 pad18[2]; s16 u1A;
    u8 pad1C[0x18]; void *u34;
} T;
void func_8016BF50(T *p) {
    s16 v[4];
    void *m = p->u34;
    v[0] = p->u12;
    v[1] = p->u16;
    v[2] = p->u1A;
    func_80149350(m, v, v);
    func_80015954(v, (u8 *)p + 4);
}
