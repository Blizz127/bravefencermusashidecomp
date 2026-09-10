/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80129258 (main_0012.s), decoded manually from
 * raw asm (0x1C bytes, no frame; NOT verified against retail;
 * C89-gated only, promotion requires an oracle MATCH): zeroes
 * the u16 tag of all 0x80 entries of 0x38 bytes from
 * &D_8011DB30 (sh in a 0x7F-downto->=0 loop, cursor advanced in
 * the branch delay slot). */

extern u8 D_8011DB30;

void func_80129258(void) {
    u8 *p;
    s32 i;

    p = &D_8011DB30;
    for (i = 0x7F; i >= 0; i--) {
        *(u16 *) p = 0;
        p += 0x38;
    }
}
