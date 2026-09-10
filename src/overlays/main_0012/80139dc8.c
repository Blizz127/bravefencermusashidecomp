/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s16 D_8012811A[];
void func_80139DC8(void) {
    s32 i = 0x287;
    s16 *p = D_8012811A;
    do { *p = 0; i--; p--; } while (i >= 0);
}
