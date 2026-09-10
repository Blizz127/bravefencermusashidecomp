/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012BEE8();
typedef struct Inner { u8 pad[4]; s32 u4; } Inner;
typedef struct {
    u8 pad[0x1C]; s32 u1C;
    Inner *inner;
} T;
s32 func_80142D38(T *p) {
    if (func_8012BEE8(p) == 1) {
        return 1;
    }
    if (p->u1C & 1) {
        p->inner->u4 |= 0x80000000;
    } else {
        p->inner->u4 &= 0x7FFFFFFF;
    }
    return 0;
}
