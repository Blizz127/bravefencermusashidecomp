#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80147060();                                  /* static */
void func_80171A1C(s32);                               /* static */
void func_80172BC8(s32);                               /* static */
extern s32 D_801150F8;

void func_80172B80(s32 arg0) {
    if (D_801150F8 == 0) {
        func_80147060();
    }
    func_80171A1C(arg0);
    func_80172BC8(arg0);
}
