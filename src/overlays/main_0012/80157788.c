/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80184280;
void func_80147078();
void func_801578C0();
void func_80157788(void *p) {
    D_80184280 = 300;
    func_80147078(p, 7);
    func_801578C0(p);
}
