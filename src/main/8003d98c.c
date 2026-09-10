/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8006B8F0;
extern CB D_8006B8EC;
void func_8003D98C(void) {
    if (D_8006B8F0)
        D_8006B8F0();
    D_8006B8EC();
}
