/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef void (*CB)();
extern CB D_80180A1C[];
void func_80149020();
void func_80147078();
void func_80159B70();
void func_80161034(u16 *p) {
    func_80149020(p);
    D_80180A1C[p[0]](p);
    func_80147078(p, 0);
    func_80159B70(p);
}
