/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80142DB8();
s32 func_80142D38();
void func_80142BB4();
void func_801428CC(void *p) {
    if (func_80142DB8(p) == 1) {
        func_80142BB4(p, 1, 3);
    } else if (func_80142D38(p) == 1) {
        func_80142BB4(p, 0, 3);
    }
}
