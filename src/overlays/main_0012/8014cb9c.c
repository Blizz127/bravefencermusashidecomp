/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
extern S D_80126C98;
extern s16 D_80126C9E;
void func_8014CB9C(S *p) {
    D_80126C98 = *p;
    D_80126C9E = 1;
}
