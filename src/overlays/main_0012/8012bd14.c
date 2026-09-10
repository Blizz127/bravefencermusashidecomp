#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80013350(s32, void *);                          /* extern */
extern s32 *D_80126B5C;

void func_8012BD14(s32 arg0) {
    func_80013350(arg0 + 4, &D_80126B5C);
}
