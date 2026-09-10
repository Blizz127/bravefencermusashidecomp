/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8012BEE8();
void func_80166244();
void func_801319E0();
void func_80131CA8();
typedef struct Inner { u8 pad[0x18]; s16 u18; u8 pad1A[2]; u16 u1C; } Inner;
typedef struct { u8 pad[0x20]; Inner *inner; u8 pad24[0x90]; s32 uB4; } T;
void func_80130974(T *p) {
    Inner *q;
    if (p->uB4 & 0x8000) {
        q = p->inner;
        if (q->u18 < 0x1000) {
            q->u18 += 0x400;
            p->inner->u1C += 0x400;
        }
        if (func_8012BEE8(p)) {
            func_80166244(p);
            func_801319E0(p);
            return;
        }
    }
    func_80131CA8(p, 0x2B);
}
