/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_8018167C[];
void func_8016DBD8();
void func_8016DA30(u16 *p) {
    func_8016DBD8(p);
    D_8018167C[p[1]](p);
}
