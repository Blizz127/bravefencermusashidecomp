/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_80013328(s32, s32);                        /* extern */

s32 func_8014C278(s32 arg0, s32 arg1, s32 arg2) {
    return func_80013328(arg0 + 4, arg1 + 4) < (arg2 & 0xFFFF);
}
