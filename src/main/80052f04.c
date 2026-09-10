#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80048EAC(void *, s32);                        /* static */
void func_8004917C(s32);                               /* static */
extern s32 *D_800A63F0;

void func_80052F04(s32 arg0) {
    func_8004917C(func_80048EAC(&D_800A63F0, arg0));
}
