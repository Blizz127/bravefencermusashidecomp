/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80172664();
typedef struct { u8 pad[0xAA]; u16 a, b; } T;
void func_801722CC(T *p) {
    if (func_80172664(p) == 0) {
        p->b = 0x40;
        p->a = 0x40;
    }
}
