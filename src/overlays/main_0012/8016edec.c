/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016EE94();
void func_801599A4();
void func_80159B3C();
extern u16 D_80126B58;
void func_8016EDEC(void *p) {
    u16 *s = &D_80126B58;
    func_8016EE94(p);
    if ((u16)(*s - 25) < 2) {
        return;
    }
    func_801599A4(s);
    func_80159B3C(s);
}
