/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168BDC();
void func_80146A6C();
typedef struct { s16 a, b; u8 pad4[0x18]; s32 u1c; } T;
void func_80168AE4(T *p) {
    func_80168BDC(p, 9, 3, 2);
    func_80168BDC(p, 9, 2, 1);
    func_80146A6C(3, p, ((s16 *)p)[3], ((s16 *)p)[5], ((s16 *)p)[7], -5, 0xC0009C00);
    p->u1c = 1;
    p->b++;
}
