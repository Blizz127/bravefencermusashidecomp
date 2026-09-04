#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80011C10();                                  /* extern */
void func_80015310();                                  /* extern */
s32 func_800D0588();                                /* extern */

void func_801284B8(void) {
    if (func_800D0588() != 0) {
        func_80015310();
        func_80011C10();
    }
}
