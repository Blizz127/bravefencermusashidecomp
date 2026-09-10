/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 pad[0x1F8]; s32 flags; } T;
void func_8016F094(T *p) {
    p->flags &= ~0x04000000;
}
