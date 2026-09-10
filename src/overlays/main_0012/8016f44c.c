/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_80029178(s32);                             /* extern */

s32 func_8016F44C(s32 arg0) {
    return (func_80029178(arg0 + 0x125) & 0xFF) != 0;
}
