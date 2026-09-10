/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_801803E4[];
void *func_801563EC(u16 a0) {
    return D_801803E4 + a0 * 12;
}
