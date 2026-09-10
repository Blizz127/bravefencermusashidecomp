/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80181B78[];
void func_801758FC();
void func_80175820();
void func_801759D8();
void func_8017553C(u8 *p) {
    D_80181B78[p[1]]();
    func_801758FC();
    func_80175820();
    func_801759D8();
}
