/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { s32 a; u8 pad[0x48]; } S;
extern S D_801269F0[];
S *func_801399A8(void) {
    s32 i;
    for (i = 1; i < 3; i++) {
        if (D_801269F0[i].a == 0) {
            return &D_801269F0[i];
        }
    }
    return 0;
}
