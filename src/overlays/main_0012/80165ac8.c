/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_801811D8[];
extern u8 D_80078EC1;
void func_80165AC8(void) {
    D_801811D8[D_80078EC1 & 0x7F]();
}
