#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800291C8(s32, s16);                            /* extern */
s32 func_800291DC();                               /* extern */
s32 func_800D0D7C(s32, s32);                            /* extern */

void func_80162120(void) {
    if ((func_800291DC(8) << 0x10) == 0) {
        func_800291C8(8, (s16) (func_800D0D7C(0, 1) | ~0x7FFF));
    }
}
