/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct { u8 b[8]; } S;
typedef struct { u8 pad[0x90]; S a; u8 pad98[0x15C-0x98]; S b; } T;
void func_8014C8F0(T *p) {
    p->b = p->a;
}
