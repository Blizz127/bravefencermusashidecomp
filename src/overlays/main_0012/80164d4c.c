/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80164E40();
void func_80146CA0();
typedef struct Inner { u8 pad[0x18]; u16 a, b; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_80164D4C(T *p) {
    Inner *in = p->inner;
    if (func_80164E40(p)) {
        func_80146CA0(p);
    } else {
        u16 v = in->b + 0x100;
        in->b = v;
        in->a = v;
    }
}
