/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80142C84();
s32 func_80143994();
void func_8012AD50();
typedef struct Inner { u8 pad[0x18]; s16 u18; } Inner;
typedef struct {
    u8 pad[0x1C]; s32 u1c;
    Inner *inner;
    u8 pad24[0x38]; s16 u5c;
    u8 pad5E[0x12]; u16 u70, u72;
    u8 pad74[0x58]; s32 cc;
    u8 padD0[0x30]; s16 u100;
} T;
void func_80142B2C(T *p) {
    p->u1c = 0x180;
    p->u5c = 0x100;
    p->u100 = p->u70 & 0x100;
    p->u70 = p->u70 & 3;
    p->u72 |= 0x1000;
    if (p->u100 == 0) {
        func_80142C84(p);
    }
    p->cc = func_80143994(p, p->inner->u18);
    func_8012AD50(p);
}
