/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8002AA3C();
s32 func_8002AA00(s32 a0) {
    s32 v = func_8002AA3C(a0);
    if (v) {
        return (a0 < v) ^ 1;
    }
    return -1;
}
