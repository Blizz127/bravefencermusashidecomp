/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
extern S D_801853C4;
extern S D_801853BC;
void func_8017B8E8(S *p) {
    D_801853C4 = p[0];
    D_801853BC = p[1];
}
