/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
extern u8 D_80078EC0;
typedef struct { u8 pad[0x1C8]; s16 u1C8; } T;
s32 func_801619D0(T *p) {
    if (p->u1C8) {
        return (D_80078EC0 & 0x7F) == 3;
    }
    return 0;
}
