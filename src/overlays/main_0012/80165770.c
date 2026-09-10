/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_800CAF6C();                                  /* extern */
extern u8 D_80078EC1;

void func_80165770(void) {
    if (D_80078EC1 == 0xC) {
        func_800CAF6C();
    }
}
