/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8004CFEC();
s32 func_8012B70C(s16 *a, s16 *b) {
    return (func_8004CFEC(a[2] - b[2], b[0] - a[0]) - 0x400) & 0xFFF;
}
