#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern s32 D_80072C70;
void func_80011778();                                  /* static */
s32 func_80019A24(void *, s32, s32, s32);                  /* static */
extern s32 *D_800AE870;

void func_800112C8(void) {
    if (func_80019A24(&D_800AE870, D_80072C70, 0, 0) != 0) {
        func_80011778();
    }
}
