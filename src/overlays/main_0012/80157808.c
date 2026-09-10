/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8018068C[];
extern s32 D_80184280;
void func_801599A4();
void func_80159B3C();
void func_80157808(u16 *p) {
    D_8018068C[p[1]]();
    if (--D_80184280 == -1) {
        func_801599A4(p);
        func_80159B3C(p);
    }
}
