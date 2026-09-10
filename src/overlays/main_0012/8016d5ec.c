/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8016CF04();
void func_80146C3C();
typedef struct Inner { u8 pad[0x18]; u16 a, b; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
void func_8016D5EC(T *p) {
    Inner *in = p->inner;
    in->a -= 0x60;
    in->b -= 0x60;
    if (func_8016CF04(p, 2) << 16) {
        func_80146C3C(p);
    }
}
