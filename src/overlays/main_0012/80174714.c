/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

s32 func_800CF8CC();                                /* extern */
void func_80147060(void *);                               /* static */
void func_8016F0AC();                                  /* static */
extern s32 *D_80126B58;

void func_80174714(void) {
    if (func_800CF8CC() == 0) {
        func_80147060(&D_80126B58);
        func_8016F0AC();
    }
}
