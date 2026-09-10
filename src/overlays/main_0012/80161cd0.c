/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_800CF8B4();
void func_80147324();
extern u16 D_80180E68[];
void func_80161CD0(void *p, u32 a1) {
    if (a1 >= 8) {
        return;
    }
    if (func_800CF8B4()) {
        func_80147324(D_80180E68[a1]);
    }
}
