/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8016F1AC();
s32 func_80029178();
extern void *D_8011F9C4;
s32 func_8015ABD4(void *p, s32 a1, s32 a2) {
    if (func_8016F1AC(p) != 0) {
        return 0;
    }
    if (a2 < a1) {
        if (D_8011F9C4 == 0) {
            return 0;
        }
        if ((func_80029178(0x21) & 0xFF) != 0) {
            return 0;
        }
    }
    return 1;
}
