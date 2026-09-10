/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x3C]; u16 f3c, f3e, f40, f42; } T;
void func_801511A8(T *p) {
    p->f3e = 0;
    p->f40 = 0;
    p->f42 = 0;
    p->f3c &= 0xFFFE;
}
