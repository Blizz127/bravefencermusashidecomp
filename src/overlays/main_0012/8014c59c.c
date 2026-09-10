/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8004CFEC();
s32 func_8014C59C(s16 *a, s16 *b) {
    return (func_8004CFEC(a[3] - b[3], a[7] - b[7])) & 0xFFF;
}
