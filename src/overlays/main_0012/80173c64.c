/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80171CC4();
void func_80171A1C();
extern s16 D_80126B36;
void func_80173C64(void *p) {
    s16 *t = &D_80126B36;
    if (*t != 0) {
        if (func_80171CC4(p, t - 3) == 0) {
            return;
        }
    }
    func_80171A1C(p);
}
