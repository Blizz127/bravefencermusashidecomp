/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80013F3C();
void func_800126C4();
void func_80012558();
void func_800123F0();
typedef struct Inner {
    u8 pad_0[16];
    s16 a;
    s16 b;
    s16 c;
    u8 pad_16[22];
    u16 flags;
} Inner;
typedef struct { u8 pad_0[32]; Inner *inner; } T;
void func_80147718(T *p) {
    Inner *q = p->inner;
    func_80013F3C((u8 *)q + 52);
    func_800126C4((u8 *)q + 52, q->a);
    func_80012558((u8 *)q + 52, q->b);
    func_800123F0((u8 *)q + 52, q->c);
    q->flags |= 1;
}
