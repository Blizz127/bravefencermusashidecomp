/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80165770(void *);                               /* static */
void func_8016F0E4(void *);                               /* static */
extern s32 *D_80126B58;

void func_8016F0AC(void) {
    func_8016F0E4(&D_80126B58);
    func_80165770(&D_80126B58);
}
