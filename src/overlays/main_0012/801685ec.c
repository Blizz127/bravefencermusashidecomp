/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80166994();
s32 func_80166690();
void func_80146C3C();
void func_801685EC(void *p) {
    func_80166994(p, 2, 2, 0);
    if ((s16)func_80166690(2, 1) == 0) {
        func_80146C3C(p);
    }
}
