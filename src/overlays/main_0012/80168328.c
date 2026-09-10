/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80166994();
s32 func_80166690();
void func_80146C3C();
typedef struct Q { u8 pad[0x44]; s32 flags; } Q;
typedef struct {
    u8 pad[2]; u16 u2;
    u8 pad4[0x18]; s32 u1C;
    u8 pad20[8]; s16 u28;
    u8 pad2A[2]; s16 u2C;
    u8 pad2E[2]; s16 u30;
    u8 pad32[2]; Q *u34;
} T;
void func_80168328(T *p) {
    if ((p->u34->flags & 2) == 0 || (p->u1C = p->u1C - 1) == 0) {
        p->u2 = p->u2 + 1;
        func_80166994(p, 2, p->u2C, 0);
    } else {
        func_80166994(p, 1, p->u2C, p->u30);
    }
    if ((s16)func_80166690(p->u2C, p->u28) == 0) {
        func_80146C3C(p);
    }
}
