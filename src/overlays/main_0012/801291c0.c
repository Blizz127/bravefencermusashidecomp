/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801291C0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): scans 0x80 entries
 * of 0x38 bytes from &D_8011DB30 for the first whose u16 tag is
 * 0, zeroes it via func_80016714(slot, 0x38) and returns it;
 * returns NULL (0) when full. Counter increments in the bnez
 * delay slot (always); the found pointer returns via the exit
 * jump's delay slot. */

extern u8 D_8011DB30;
extern void func_80016714(void *arg0, s32 arg1);

u8 *func_801291C0(void) {
    u8 *s0;
    s32 i;

    s0 = &D_8011DB30;
    for (i = 0; i < 0x80; i++) {
        if (*(u16 *) s0 == 0) {
            func_80016714(s0, 0x38);
            return s0;
        }
        s0 += 0x38;
    }
    return 0;
}
