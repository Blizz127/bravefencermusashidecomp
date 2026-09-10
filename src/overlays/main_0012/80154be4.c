/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154C24();
void func_80154F9C();
void func_80154BE4(void *p) {
    s32 a;
    s32 b;
    a = 0;
    b = 0;
    func_80154C24(p, &a, &b);
    func_80154F9C(p);
}
