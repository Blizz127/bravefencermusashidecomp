/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_801497A8();
void func_801599A4();
void func_80149864();
s32 func_80161BE0(void *p) {
    if (func_801497A8(p) == 0) {
        return 0;
    }
    func_801599A4(p);
    func_80149864(p);
    return 1;
}
