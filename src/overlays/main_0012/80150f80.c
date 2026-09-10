/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80151184();
extern u8 D_80078EC1;
void func_80150F80(void *p) {
    if (D_80078EC1 != 0xC) {
        func_80151184(p, 0xC007, 0x20);
    }
}
