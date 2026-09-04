#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8002A544();                                 /* static */
extern s32 D_80078E88;

void func_8002959C(void) {
    func_8002A544(0x32);
    D_80078E88 += 1;
}
