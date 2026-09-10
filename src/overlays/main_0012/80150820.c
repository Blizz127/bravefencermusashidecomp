/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014BD24();
void func_8014ACE8();
void func_80150820(void *p, void *a1) {
    if (a1) {
        func_8014BD24(p, a1);
        func_8014ACE8(p, 4, a1);
    }
}
