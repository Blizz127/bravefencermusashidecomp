/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016E3CC();
void func_80146C3C();
typedef struct Inner { u8 pad[0x18]; s16 a, b; } Inner;
typedef struct { u8 pad[0x1C]; s32 t; Inner *inner; } T;
void func_8016E2E8(T *p) {
    Inner *in = p->inner;
    func_8016E3CC(p);
    p->t--;
    if (p->t != 0) {
        in->a -= 0x100;
        in->b -= 0x120;
    } else {
        func_80146C3C(p);
    }
}
