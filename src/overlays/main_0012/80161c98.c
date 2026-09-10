/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147324();
extern u16 D_80180E58[];
void func_80161C98(s32 a0, u32 a1) {
    if (a1 < 8) {
        func_80147324(D_80180E58[a1]);
    }
}
