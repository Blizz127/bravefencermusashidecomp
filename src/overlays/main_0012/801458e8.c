#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800D185C(void *);                               /* extern */
extern s32 *D_80078E50;
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s16 D_800B9A0A;

void func_801458E8(void) {
    D_800AE6B0 = D_800AE6AC | 0x01000000;
    func_800D185C(&D_80078E50);
    D_800B9A0A = 0x3000;
}
