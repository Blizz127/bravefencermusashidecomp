/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154150();
void func_80146E90();
void func_80148534();
void func_80146A6C();
void func_80147324();
void func_801725B8();
void func_80146CA0();
typedef struct {
    u8 pad[6]; s16 a; u8 pad8[2]; u16 b; u8 padC[2]; s16 c;
    u8 pad10[0x234]; u8 u244, u245;
} T;
void func_8015F380(T *p) {
    s16 t0[4];
    s16 t1[4];
    func_80154150(p, 0x18);
    p->u244 = 0;
    p->u245 = 0;
    func_80146E90(p, 0);
    func_80148534(t0, t1);
    func_80146A6C(0x25, p, p->a, (s16)(p->b - 0x14), p->c, 0, 0);
    func_80146A6C(0x25, p, p->a, (s16)(p->b - 0x14), p->c, 1, 0);
    func_80147324(0x56D);
    func_801725B8(p);
    func_80146CA0(p);
}
