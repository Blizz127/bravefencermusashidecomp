/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    void *u0;
    s16 u4;
    u8 pad6[0x19]; s8 u1F;
} T;
s32 func_801399F0(T *p) {
    if (p->u0 == 0 || p->u4 == 0 || p->u4 == 0xE) {
        return -1;
    }
    if (p->u4 != 0xD) {
        return 0;
    }
    return p->u1F;
}
