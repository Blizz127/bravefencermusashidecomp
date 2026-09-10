/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u16 D_80078EB6;
void func_8014BCEC(s32 unused, s32 a1) {
    D_80078EB6 = D_80078EB6 + a1;
    if (D_80078EB6 >= 0x663) {
        D_80078EB6 = 0x662;
    }
}
