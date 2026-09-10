/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014ACE8();
void func_80151204(void *p, s32 a1) {
    if (a1 && a1 != 0x3E8) {
        func_8014ACE8(p, 1, a1 & 0x7FFF);
    }
}
