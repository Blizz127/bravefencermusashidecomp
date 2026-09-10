/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 D_80126D50;

void func_80171904(s32 arg0) {
    D_80126D50 = arg0 | (D_80126D50 & 0x7F000000);
}
