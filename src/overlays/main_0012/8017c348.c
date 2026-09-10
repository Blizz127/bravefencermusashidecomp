/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80115112;
void func_8017C348(void) {
    u16 *p = &D_80115112;
    *p = *p + 1;
}
