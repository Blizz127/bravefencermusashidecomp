/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168BDC();
void func_801687CC();
typedef struct { u16 a, b; } T;
void func_80168780(T *p) {
    func_80168BDC(p, 8, 0, 2);
    func_801687CC(p);
    p->b += 1;
}
