/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8017F9B4[];
extern s16 D_801270C0;
void func_80142978(u16 *p) {
    if (D_801270C0 != 3)
        D_8017F9B4[p[1]]();
}
