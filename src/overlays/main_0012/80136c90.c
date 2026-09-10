/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[10]; } S;
extern S D_80182F70;
void func_8001534C();
void func_80136C90(void) {
    S tmp;
    tmp = D_80182F70;
    func_8001534C(0, &tmp, 0x78, 0x10, 0, 0);
}
