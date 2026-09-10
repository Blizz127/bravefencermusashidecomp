/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016E7C8();
typedef struct {
    u8 pad[0x12]; u16 u12;
    u8 pad14[2]; s16 u16;
} T;
void func_8016E778(T *p) {
    s16 v[4];
    u16 t;
    s32 u;
    s32 hi;
    t = p->u12;
    v[2] = t;
    v[1] = t;
    v[0] = t;
    u = p->u16;
    hi = (u << 16) | (u << 8);
    u = u | hi;
    func_8016E7C8(p, v, &u);
}
