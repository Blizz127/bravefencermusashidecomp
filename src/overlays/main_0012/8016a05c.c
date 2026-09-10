/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80078EC0;
typedef struct { u8 pad[2]; u16 u2; } T;
void func_8016A05C(T *p) {
    if (D_80078EC0 & 0x7F) {
        p->u2 = p->u2 + 1;
    } else {
        p->u2 = 2;
    }
}
