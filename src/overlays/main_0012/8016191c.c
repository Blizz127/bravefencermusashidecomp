/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014C010();
s32 func_8016191C(void *p, s32 a1) {
    if (a1 & 1) {
        func_8014C010(p, 1);
        return 1;
    }
    if (a1 & 0x4000) {
        func_8014C010(p, 1);
        return 2;
    }
    if (a1 & 0x2000) {
        func_8014C010(p, 1);
        return 4;
    }
    return 0;
}
