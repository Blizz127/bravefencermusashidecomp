/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146AFC();
typedef struct { s16 a, b, c, d; void *p; s32 x, y; } P;
void func_8014C010(void *a0, void *a1) {
    P s;
    s.a = 2;
    s.b = 0;
    s.c = 0;
    s.d = 0;
    s.p = a0;
    s.x = a1;
    s.y = 0;
    func_80146AFC(&s);
}
