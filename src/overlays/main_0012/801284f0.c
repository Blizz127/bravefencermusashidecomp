#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80011C10();                                  /* extern */
void func_8016E8F0();                                  /* static */
void func_80175308();                                  /* static */
void func_80175494();                                  /* static */
extern u8 D_800B9A64;

void func_801284F0(void) {
    func_80175308();
    func_8016E8F0();
    if (D_800B9A64 != 0) {
        func_80175494();
    }
    func_80011C10();
}
