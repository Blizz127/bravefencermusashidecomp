/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

typedef struct {
    s16 x;
    s16 pad[7];
} T_800152F4;

extern T_800152F4 D_800B93D8[];

void func_800152F4(s16 i) {
    D_800B93D8[i].x = 0;
}
