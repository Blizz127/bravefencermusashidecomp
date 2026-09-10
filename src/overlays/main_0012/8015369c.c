/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8011DB28;
void func_8015369C(u8 *p) {
    if (D_8011DB28)
        D_8011DB28(p + 0xA0);
    p[0xDE] = 0x5A;
}
