/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80139A8C();
void func_80139B18();
typedef struct {
    u8 pad[4]; s16 u4;
    u8 pad6[2]; s32 u8;
    u8 padC[0xA]; u16 u16;
    u8 pad18[6]; u8 u1E;
    u8 pad1F[0xF]; s16 u2E;
} T;
void func_8013A0A4(T *p) {
    if (p->u1E == 0) {
        p->u1E = 4;
    } else {
        p->u1E += 5;
    }
    if (p->u1E >= 0xC) {
        p->u16 = (p->u16 + 1) % (p->u2E + 1);
        p->u1E = 0;
        if (p->u8 & 0x100) {
            p->u4 = 6;
        } else {
            p->u4 = 2;
        }
    }
    func_80139A8C(p);
    func_80139B18(p);
}
