/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8005C604();
extern s32 D_80073B24;
void func_800530D4(s16 *p) {
    func_8005C604(&D_80073B24, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
}
