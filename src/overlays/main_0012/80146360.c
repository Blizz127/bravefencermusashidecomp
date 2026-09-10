/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8017FE70[];
extern u8 D_80126BA4;
extern s32 D_80126B58;
void func_80146360(void) {
    D_8017FE70[D_80126BA4](&D_80126B58);
}
