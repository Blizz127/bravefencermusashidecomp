#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80078EFC;
extern s32 D_80078F00;

void func_8002A6F0(void) {
    s32 var_v1;

    var_v1 = D_80078EFC + 1;
    if (var_v1 >= 0x1F) {
        var_v1 = 0x1E;
    }
    D_80078EFC = var_v1;
    D_80078F00 = 0;
}
