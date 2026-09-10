/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180FE4[];
extern u8 D_80078EC5;
extern u8 D_80078EC1;
void func_80165B28();
void func_80165580(void *p) {
    if (D_80078EC5 & 0x80)
        func_80165B28(p);
    else
        D_80180FE4[D_80078EC1 & 0x7F]();
}
