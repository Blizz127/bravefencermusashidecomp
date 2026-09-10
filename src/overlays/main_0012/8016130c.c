/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801599A4();
void func_8015BDD0();
void func_8015BF48();
s32 func_8016130C(void *p, u32 a1) {
    if (a1 == 0 || a1 == 0x8000) {
        func_801599A4(p);
        func_8015BDD0(p);
        return 1;
    }
    if (a1 & 0x4000) {
        func_801599A4(p);
        func_8015BF48(p);
        return 1;
    }
    return 0;
}
