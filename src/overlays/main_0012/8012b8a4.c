/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s16 D_80126B66;
extern s16 D_80126B5E;
s32 func_8004CFEC();
s32 func_8012B8A4(s16 *p) {
    return (func_8004CFEC(p[7] - D_80126B66, D_80126B5E - p[3]) - 0x400) & 0xFFF;
}
