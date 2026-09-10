#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8012A048(void *, s32, s32);                     /* static */
extern s32 *D_80126948;

void func_8012A018(s32 arg0, s32 arg1) {
    func_8012A048(&D_80126948, arg0, arg1 & 0xFF);
}
