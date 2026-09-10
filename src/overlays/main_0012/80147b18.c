/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80147D38();
void func_80147B5C();
void func_80147B18(void *p, s32 a1, s32 a2, s32 a3) {
    s32 tmp[4];
    func_80147D38(p, a1, a2, a3, tmp);
    func_80147B5C(p, tmp);
}
