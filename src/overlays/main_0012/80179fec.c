/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80179B74();
void func_80179FEC(s16 *p) {
    s16 sp[5];
    sp[0] = 0x20;
    sp[1] = p[0];
    sp[2] = p[1];
    sp[3] = p[2];
    sp[4] = p[3];
    func_80179B74(sp);
}
