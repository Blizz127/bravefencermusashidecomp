/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80146C3C();
typedef struct { u16 id; u8 pad[0x56]; } S;
extern S D_8011D030[];
void func_8016706C(s16 id) {
    s16 i = 0;
    S *s = D_8011D030;
    for (; i < 0x1E; i++, s++) {
        if (s->id == id) {
            func_80146C3C(s);
        }
    }
}
