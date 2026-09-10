/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8002D4C8();
void func_80131CA8();
typedef struct Inner {
    u8 pad[0x18]; s16 u18, u1A, u1C;
    u8 pad1E[0xE]; u16 u2C;
} Inner;
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    Inner *inner;
    u8 pad24[0x38]; s16 u5C;
    u8 pad5E[0x3A]; s16 u98;
    u8 pad9A[0x10]; s16 uAA;
    u8 padAC[8]; s32 uB4;
    u8 padB8[9]; u8 uC1;
} T;
void func_801308DC(T *p) {
    p->uC1 = 0xE;
    if (p->uB4 & 0x8000) {
        p->u1C = 0x10;
        p->uAA = 0;
        p->u5C = 0;
        p->u98 = 0;
        p->inner->u18 = 0x400;
        p->inner->u1C = 0x400;
        p->inner->u1A = 0x200;
        p->inner->u2C |= 0x10;
        func_8002D4C8(0x68A, 0);
    }
    func_80131CA8(p, 0x2A);
}
