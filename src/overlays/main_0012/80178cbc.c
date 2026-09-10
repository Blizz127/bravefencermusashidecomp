#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80184F38;
void func_80178D40(s32, s32);                          /* static */
extern s16 D_80185C7C;

void func_80178CBC(s32 arg0, s32 arg1) {
    D_80184F38 = arg1;
    do {
        func_80178D40(arg0, D_80184F38);
    } while (D_80185C7C == 3);
}
