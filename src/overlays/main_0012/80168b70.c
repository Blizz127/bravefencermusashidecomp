/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168BDC();
void func_80146C3C();
typedef struct { u8 pad[0x1C]; s32 t; } T;
void func_80168B70(T *p) {
    p->t--;
    if (p->t != -1) {
        func_80168BDC(p, 9, 3, 1);
    } else {
        func_80168BDC(p, 9, 2, 1);
        func_80146C3C(p);
    }
}
