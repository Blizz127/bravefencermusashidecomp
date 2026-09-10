#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_8004914C();                                  /* extern */
void func_800491AC(s32);                               /* extern */
void func_8004945C(s32, s32, void *);                         /* extern */

void func_8012F14C(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    func_8004914C();
    func_800491AC(arg0);
    func_8004945C(arg1, arg2, &sp10);
}
