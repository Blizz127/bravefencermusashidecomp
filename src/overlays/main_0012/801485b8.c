/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801485B8(s8 *src, s16 *xy, s16 *uv) {
    xy[0] = src[0];
    xy[1] = src[1];
    xy[2] = src[2];
    uv[0] = src[3];
    uv[1] = src[4];
    uv[2] = src[5];
}
