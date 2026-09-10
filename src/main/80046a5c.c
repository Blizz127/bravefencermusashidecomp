/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80043B1C();
void func_80043A18();
extern s32 D_800A2BA4;
extern s32 D_80078800;
extern s32 D_80078804;
s32 func_80046A5C(void *p) {
    if (D_800A2BA4) {
        return -1;
    }
    func_80043A18(func_80043B1C(&D_80078800) + 1, p);
    return D_80078804;
}
