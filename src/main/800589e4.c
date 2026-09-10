/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_800599B8();
s32 func_80058B7C();
typedef struct { s16 a, b, c, d; } S;
u32 func_800589E4(void *p, s32 a1, s32 a2) {
    S s;
    s.c = 0x10;
    s.a = a1;
    s.b = a2;
    s.d = 1;
    func_800599B8(&s, p);
    return (u16)func_80058B7C(a1, a2);
}
