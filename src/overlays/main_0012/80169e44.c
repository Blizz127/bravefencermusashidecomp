/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80128ED8();
void func_80146C3C();
void *func_80146A6C();
typedef struct {
    u8 pad[6]; s16 u6; u8 pad8[2]; s16 uA; u8 padC[2]; s16 uE;
    u8 pad10[2]; u16 u12; u8 pad14[2]; u16 u16; u8 pad18[2]; u16 u1A;
    s32 u1C;
    void *inner;
} T;
typedef struct { u8 pad[0x12]; u16 u12; u8 pad14[2]; u16 u16; u8 pad18[2]; u16 u1A; } R;
void func_80169E44(T *p) {
    R *r;
    if (func_80128ED8(p->inner, (u8 *)p + 0x24)) {
        func_80146C3C(p);
        return;
    }
    if (p->u1C++ >= 3) {
        return;
    }
    r = func_80146A6C(9, p, p->u6, p->uA, p->uE, p->u1C & 1, 0);
    if (r) {
        r->u12 = p->u12;
        r->u16 = p->u16;
        r->u1A = p->u1A;
    }
}
