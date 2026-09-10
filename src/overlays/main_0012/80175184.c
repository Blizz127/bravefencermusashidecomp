/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80181A08[];
void func_80175268();
void func_80175184(u16 *p) {
    u16 idx = p[1];
    if (idx < 2)
        D_80181A08[idx]();
    else
        func_80175268();
}
