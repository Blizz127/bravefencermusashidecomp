/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146750();
void func_8014680C();
typedef struct { s16 a, b, c, d; void *p; s32 x, y; } P;
void func_801466F0(s16 a0, void *a1, s16 a2, s16 a3, s16 a4, s32 a5, s32 a6, s32 a7) {
    P s;
    s.a = a0;
    s.p = a1;
    s.b = a2;
    s.c = a3;
    s.d = a4;
    s.x = a5;
    s.y = a6;
    if (a7) {
        func_80146750(&s);
    } else {
        func_8014680C(&s);
    }
}
