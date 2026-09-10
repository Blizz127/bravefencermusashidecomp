/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s16 kind; u8 pad[0xE]; } S;
extern S D_8011DA80[];
S *func_8013A8BC(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_8011DA80[i].kind == 0) {
            return &D_8011DA80[i];
        }
    }
    return 0;
}
