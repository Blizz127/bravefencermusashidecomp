/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[0xC]; s32 c, pad10, c14;
    u8 pad18[8]; s16 u20, u22, u24;
    u8 pad26[8]; s16 u2E, u30, u32;
    u8 pad34[0x20]; s32 u54;
} T;
void func_80174BBC(T *p) {
    p->c = 0x12C;
    p->c14 = 0x12C;
    p->u20 = 0x155;
    p->u22 = 0x800;
    p->u24 = 0;
    p->u2E = 0;
    p->u30 = -0x28;
    p->u32 = 0;
    p->u54 = 0;
}
