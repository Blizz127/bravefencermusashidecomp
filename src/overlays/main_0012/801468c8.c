/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 used; u8 pad[3]; s32 ptr; u8 rest[0x24]; } S;
extern S D_8011F750[];
S *func_801468C8(s32 a0, s32 a1) {
    s32 i;
    for (i = 0; i < 2; i++) {
        if (D_8011F750[i].used == 0) {
            D_8011F750[i].ptr = a0;
            D_8011F750[i].used = a1;
            return &D_8011F750[i];
        }
    }
    return 0;
}
