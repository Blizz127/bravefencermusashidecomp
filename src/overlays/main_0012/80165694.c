/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern s32 D_80078EC8;
typedef struct { u8 pad[0x1F8]; s32 u1F8; } T;
void func_80165694(T *p) {
    if ((p->u1F8 & 0x80FFFFFF) == 0 && D_80078EC8) {
        D_80078EC8 = D_80078EC8 - 1;
    }
}
