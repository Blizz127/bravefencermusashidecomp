/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80128ED8();
void func_80146C3C();
typedef struct Inner {
    u8 pad[8]; s32 u8;
    u8 padC[0xB]; u8 u27;
    u8 pad28[0xF0]; /* unused */
    u8 pad18off[0];
} Inner;
typedef struct Inner2 {
    u8 pad[0x18]; s16 u18, u1A;
    u8 pad1C[0xB]; u8 u27;
} I;
typedef struct {
    u8 pad[8]; s32 u8;
    u8 padC[4]; s32 u10, u14;
    u8 pad18[8]; I *inner;
    u8 pad24[4]; u8 u28;
} T;
void func_8016DB34(T *p) {
    I *in = p->inner;
    if (func_80128ED8(in, (u8 *)p + 0x24)) {
        func_80146C3C(p);
        return;
    }
    in->u27 = p->u28 - 0x70;
    p->u10 += 0xFFFA0000;
    p->u14 += p->u10;
    p->u8 += p->u14;
    in->u18 -= 0x500;
    in->u1A -= 0x300;
}
