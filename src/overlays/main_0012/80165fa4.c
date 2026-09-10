/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80013F3C();
void func_80020F34();
void func_80048FBC();
typedef struct { u8 pad[0x20]; u8 *inner; } T;
void func_80165FA4(T *p, void *a1, void *a2) {
    s16 mtx[16];
    func_80013F3C(mtx);
    func_80020F34(mtx, p->inner + 0x18);
    func_80048FBC(mtx, a1, a1);
    func_80048FBC(mtx, a2, a2);
}
