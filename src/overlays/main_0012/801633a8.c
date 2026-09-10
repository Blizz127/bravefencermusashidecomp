/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80115200[];
extern u8 *D_80115100[];
s32 func_801633A8(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (D_80115200[i]) {
            if ((*(u16 *)(D_80115100[i] + 0x5C) & 0x400) == 0) {
                return D_80115200[i];
            }
        }
    }
    return 0;
}
