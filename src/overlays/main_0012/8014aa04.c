/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u8 D_80078EC0;

void func_8014AA04(s32 arg0) {
    D_80078EC0 = arg0 | (D_80078EC0 & 0x80);
}
