/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80148534();
void func_80149374();
typedef struct Inner { u8 pad[0xC]; u16 c, e, ten; } Inner;
typedef struct {
    u16 kind; u8 pad2[2]; s16 pad4; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[0x68]; Inner *p78;
} U;
typedef struct { u8 pad[0x18C]; U *u18C; } T;
void func_8015E40C(T *p) {
    s16 a[4];
    s16 b[4];
    U *q = p->u18C;
    if (q != 0 && q->kind != 0) {
        func_80148534(a, b);
        q->u6 = b[0] + q->p78->c;
        q->uA = b[1] + q->p78->e;
        q->uE = b[2] + q->p78->ten;
        func_80149374(p, (u8 *)q + 4);
    }
}
