/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014AD30();
extern s32 D_80115200[];
extern s32 D_80126B18[];
void func_801636D0(void *p, u32 a1) {
    u32 i;
    for (i = 0; i < 3; i++) {
        if (D_80115200[i] & 1) {
            func_8014AD30(p, &D_80126B18[i * 2], 0, (u16)(a1 & 0x7FFF));
        }
    }
}
