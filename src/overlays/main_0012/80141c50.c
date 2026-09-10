#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

s32 func_80015144();                                /* extern */
extern u16 D_8011511C;
extern u16 D_8011511E;

s32 func_80141C50(void) {
    if ((D_8011511C == 0x90F) && (D_8011511E & 0x800)) {
        return func_80015144() != 0;
    }
    return 0;
}
