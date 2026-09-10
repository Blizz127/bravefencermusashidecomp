/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8001903C();
extern u16 D_80115112;
void func_801417C4(void) {
    u16 *p = &D_80115112;
    func_8001903C();
    *p = *p + 1;
}
