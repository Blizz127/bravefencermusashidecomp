/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80168BDC();
void func_80146A6C();
void func_80168A14(s16 *p) {
    func_80168BDC(p, 8, 1, 2);
    func_80146A6C(3, p, p[3], p[5], p[7], -5, 0xC0009C00);
    p[1]++;
}
