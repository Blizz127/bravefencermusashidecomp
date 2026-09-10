/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80151184();
extern s16 D_800B9A08;
void func_80151038(void *p) {
    s32 a2 = 0x18;
    if (D_800B9A08 == 0x30A0) {
        a2 = 0x30;
    }
    func_80151184(p, 0xC00C, a2);
}
