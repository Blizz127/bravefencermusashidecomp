/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8005C49C();
s32 func_80029CD4(s32 a0) {
    if (a0 == 0) {
        return 0;
    }
    return func_8005C49C() % a0;
}
