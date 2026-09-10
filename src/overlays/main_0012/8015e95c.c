#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80146A6C(s32, s32, s32, s32, s32, s32, s32);       /* static */
void func_8015E9B8(s32);                               /* static */
extern u8 D_80078EC0;

void func_8015E95C(s32 arg0) {
    if (!(D_80078EC0 & 0x80)) {
        func_80146A6C(0x14, arg0, 0, 0, 0, 0, 0);
    }
    func_8015E9B8(arg0);
}
