/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void *func_8012C658();
typedef struct Inner { u8 pad[0x12]; u16 u12; } Inner;
typedef struct { u8 pad[0xFC]; u16 uFC; } R;
typedef struct { u8 pad[0x20]; Inner *inner; } T;
R *func_80143B6C(T *p, s32 a1) {
    R *v = func_8012C658(0x1C, a1, p);
    if (v && p->inner && a1 == 0) {
        v->uFC = p->inner->u12;
    }
    return v;
}
