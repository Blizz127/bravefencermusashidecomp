/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80059A80();
void func_800183E0();
extern u8 D_801801AC[];
void func_801550FC(s32 a0) {
    if (a0 & 0x40000000) {
        func_80059A80(D_801801AC + ((a0 & 0xFF) * 8), 0x200, 0x100);
    } else {
        func_800183E0(a0);
    }
}
