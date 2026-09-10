/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
s32 func_8001B22C();
void func_8001931C();
void func_80139788();
void func_80139A8C();
void func_80139B18();
typedef struct { u8 pad[4]; s16 u4; u8 pad6[2]; s32 u8; } T;
void func_80139FE8(T *p) {
    s32 v = func_8001B22C(p);
    if (v == 2 || v == 4) {
        p->u4 = 2;
    } else if (v == 0) {
        if (p->u8 & 1) {
            func_8001931C();
        } else {
            p->u8 = (p->u8 & ~0x10000) | 0x20020;
            func_80139788();
        }
        p->u4 = 2;
    } else {
        func_80139A8C(p);
        if (p->u8 & 0x20) {
            p->u4 = 2;
        }
    }
    func_80139B18(p);
}
