/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u16 id; u8 pad[0x66]; } S;
extern S D_8011F9D0[];
S *func_8014C088(s32 unused, s32 id) {
    S *s = D_8011F9D0;
    S *end = D_8011F9D0 + 0x1E;
    while (s < end) {
        if (s->id == id) {
            return s;
        }
        s++;
    }
    return 0;
}
