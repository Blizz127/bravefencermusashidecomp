/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80164E40();
void func_80146CA0();
typedef struct Inner { u8 pad[0x18]; s16 a, b; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x3C]; s16 u60, u62;
} T;
void func_80164CD4(T *p) {
    Inner *in = p->inner;
    func_80164E40(p);
    p->u60 += p->u62;
    in->b += p->u60;
    in->a = in->b;
    if (p->u60 < 0) {
        func_80146CA0(p);
    }
}
