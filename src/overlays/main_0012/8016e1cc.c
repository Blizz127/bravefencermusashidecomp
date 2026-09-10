/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016E3CC();
void func_80146A6C();
typedef struct Inner { u8 pad[0x18]; s16 a, b; } Inner;
typedef struct { u8 pad[2]; s16 u2; u8 pad4[0x18]; s32 t; Inner *inner; } T;
void func_8016E1CC(T *p) {
    Inner *in = p->inner;
    func_8016E3CC(p);
    p->t--;
    if (p->t != 0) {
        func_80146A6C(0x48, p, 0, 0, 0, 0x8000, 0);
        in->a += 0x100;
        in->b += 0x140;
    } else {
        p->t = 0x20;
        p->u2++;
    }
}
