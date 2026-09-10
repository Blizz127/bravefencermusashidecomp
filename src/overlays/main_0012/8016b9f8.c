/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_801846B8;
s32 func_8012EFB8();
void func_80015954();
s32 func_8016B9F8(u8 *p) {
    s16 tmp[4];
    s32 v = func_8012EFB8(&D_801846B8, tmp);
    func_80015954(tmp, p + 4);
    return (v & ~0x1000) != 0;
}
