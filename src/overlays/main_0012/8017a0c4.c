/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s32 D_80185364;
void func_80179B74(s16 *);                             /* static */

void func_8017A0C4(s32 arg0) {
    s16 sp10;

    D_80185364 = arg0;
    sp10 = 0x16;
    func_80179B74(&sp10);
}
