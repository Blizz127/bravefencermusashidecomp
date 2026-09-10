/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80014E80();
void func_8001931C();
extern s16 D_8012752C;
typedef struct {
    u8 pad[4]; s16 u4;
    u8 pad6[2]; s32 u8;
    u8 padC[0xC]; u16 u18;
    u8 pad1A[0x26]; s16 *u40;
} T;
void func_80139B18(T *p) {
    if (p->u8 & 0x6000) {
        return;
    }
    if ((func_80014E80(0, 0x10) << 16) == 0) {
        return;
    }
    if (p->u8 & 0x10000) {
        p->u8 &= ~0x10000;
        func_8001931C();
        D_8012752C = 0;
    }
    if (p->u8 & 0x2000) {
        p->u4 = 0xD;
        return;
    }
    p->u4 = 0xC;
    p->u8 &= ~0x1000;
    if (p->u40 && p->u18) {
        p->u40[0] = 3;
    }
}
