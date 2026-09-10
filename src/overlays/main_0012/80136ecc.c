/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80051DC8();
extern u16 D_800B9A02;
extern u8 D_800A6518[];
typedef struct { s32 tag; s16 x, y, w, h; u8 r, g, b; } P;
void func_80136ECC(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b) {
    P s;
    s.tag = 0;
    s.x = x;
    s.y = y;
    s.w = w;
    s.h = h;
    s.r = r;
    s.g = g;
    s.b = b;
    func_80051DC8(&s, D_800A6518 + D_800B9A02 * 20, 0);
}
