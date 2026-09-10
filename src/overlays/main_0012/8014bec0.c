/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80029124(s32, s32);                              /* extern */
extern u8 D_80078EC0;

void func_8014BEC0(void) {
    D_80078EC0 |= 1;
    func_80029124(0x80, 1);
}
