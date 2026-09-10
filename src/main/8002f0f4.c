/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s32 a; u8 pad[8]; } S;
extern u8 D_800A64B0[];
S *func_8002F0F4(void) {
    S *s = (S *)D_800A64B0;
    s32 i;
    for (i = 0; i < 8; i++, s++) {
        if (s->a == 0) {
            return s;
        }
    }
    return 0;
}
