/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct Inner { u8 pad[4]; s32 u4; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x1FC]; u8 u220, u221, u222;
} T;
void func_801470C0(T *p) {
    Inner *in = p->inner;
    if (in) {
        if (p->u221 | p->u220 | p->u222) {
            in->u4 |= 0x80000000;
        } else {
            in->u4 &= 0x7FFFFFFF;
        }
    }
}
