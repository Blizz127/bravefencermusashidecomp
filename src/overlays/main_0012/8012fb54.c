/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801319E0();
s16 *func_80143B6C();
void func_8002D4C8();
void func_80131CA8();
typedef struct {
    u8 pad[4]; s32 u4, u8, uC;
    s32 u10, u14, u18, u1C;
    u8 pad20[0x8C]; u16 uAC;
    u8 padAE[6]; s32 uB4;
} T;
typedef struct { u8 pad[0xA]; s16 uA; } R;
void func_8012FB54(T *p) {
    R *r;
    if (p->uB4 & 0x10000) {
        p->u4 += p->u10;
        p->u8 += p->u14;
        p->uC += p->u18;
        p->u1C--;
        if (p->u1C == 0) {
            func_801319E0(p);
        } else {
            r = func_80143B6C(p, 1);
            if (r) {
                r->uA += p->uAC;
            }
            if (p->u1C == 0x13) {
                func_8002D4C8(0x8F2, 0);
            }
        }
    }
    func_80131CA8(p, 0x36);
}
