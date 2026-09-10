/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0x20]; u8 u20;
    u8 pad21; u8 u22;
    u8 pad23; u16 u24, u26;
    u8 pad28[8]; s16 u30, u32, u34, u36;
} T;
void func_80139C7C(T *p) {
    s32 a1;
    if (p->u20) {
        if (p->u22 & 8) {
            a1 = (p->u34 + 0x28) >> 1;
        } else {
            a1 = ((p->u34 + 0x28) >> 1) - 0x28;
        }
    } else {
        a1 = (s16)p->u34 >> 1;
    }
    p->u30 = p->u24 - a1;
    p->u32 = p->u26 - (p->u36 >> 1);
}
