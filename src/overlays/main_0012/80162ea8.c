/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80013F3C();
void func_80012558();
void func_800123F0();
void func_800126C4();
typedef struct Inner {
    u8 pad_0[16];
    s16 c;
    s16 a;
    s16 b;
} Inner;
typedef struct {
    u8 pad_0[32];
    Inner * inner;
} T;
void func_80162EA8(T *p) {
    Inner *q = p->inner;
    func_80013F3C((u8 *)q + 52);
    func_80012558((u8 *)q + 52, q->a);
    func_800123F0((u8 *)q + 52, q->b);
    func_800126C4((u8 *)q + 52, q->c);
}
