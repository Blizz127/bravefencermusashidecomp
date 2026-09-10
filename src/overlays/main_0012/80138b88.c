/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
typedef struct {
    u8 pad[4]; s16 u4;
    u8 pad6[2]; s32 u8;
    u8 padC[0xC]; u16 u18;
    u8 pad1A[0x26]; s16 *u40;
} T;
void func_80138B88(T *p) {
    if (p->u8 & 0x2000) {
        p->u4 = 0xD;
    } else {
        p->u4 = 0xC;
        p->u8 &= -0x1001;
        if (p->u40 != 0 && p->u18 != 0) {
            p->u40[0] = 3;
        }
    }
}
