/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80078EB2;
void func_8014BC0C(s32 unused, s32 a1) {
    D_80078EB2 = D_80078EB2 + a1;
    if (D_80078EB2 >= 0x1F5) {
        D_80078EB2 = 0x1F4;
    }
}
