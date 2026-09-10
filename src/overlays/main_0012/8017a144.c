/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 D_8018538C;
void func_80179B74(s16 *);                             /* static */

void func_8017A144(s32 arg0) {
    s16 sp10;

    sp10 = 0x1B;
    func_80179B74(&sp10);
    D_8018538C = arg0;
}
