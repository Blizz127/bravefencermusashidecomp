/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146C3C();
void func_80166994();
typedef struct Inner { u8 pad[0x44]; s32 flags; } Inner;
typedef struct {
    u8 pad[2]; u16 u2; u8 pad4[0x26]; s16 u2A, u2C;
    u8 pad2E[6]; Inner *p34;
} T;
void func_801684B4(T *p) {
    if ((p->p34->flags & 2) == 0) {
        func_80146C3C(p);
    } else {
        p->u2A--;
        if (p->u2A == 0) {
            func_80166994(p, 0, 2, 0);
            p->u2++;
        }
    }
}
