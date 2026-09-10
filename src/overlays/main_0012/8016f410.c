/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8016F44C();
void func_8016F470();
s32 func_8016F410(void *p) {
    if (func_8016F44C(p) == 0) {
        return 0;
    }
    func_8016F470(p);
    return 1;
}
