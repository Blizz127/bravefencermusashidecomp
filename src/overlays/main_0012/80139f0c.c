/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_80138DB8();
void func_8002D4C8();
void func_80139B18();
extern void *D_80127524;
typedef struct { u8 pad[4]; s16 u4; u8 pad6[2]; s32 u8; } T;
void func_80139F0C(T *p) {
    s32 a2;
    if (D_80127524 != p && (p->u8 & 0x2000) == 0) {
        p->u4 = 4;
        return;
    }
    a2 = (p->u8 & 0x4000) ? 0x70 : 0x60;
    if ((func_80138DB8(p, 0, a2) << 16) == 0) {
        func_80139B18(p);
        return;
    }
    p->u4 = 2;
    if ((p->u8 & 0x20000) == 0) {
        p->u8 &= ~0x20;
    }
    func_8002D4C8(0x88D, 0);
    func_80139B18(p);
}
