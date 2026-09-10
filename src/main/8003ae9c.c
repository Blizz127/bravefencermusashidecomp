/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8003AB84();
extern u16 D_8006B564;
extern s32 D_8006B574;
s32 func_8003AE9C(s32 a0, s32 a1) {
    func_8003AB84(2, D_8006B564 << D_8006B574);
    func_8003AB84(0);
    func_8003AB84(3, a0, a1);
    return a1;
}
