/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016F264();
void func_80165840();
void func_801658DC();
void func_80165A20();
void func_80165A78();
void func_8014BF48();
void func_8014CBF8();
void func_8014B160();
void func_80149020();
void func_80146CA0();
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s32 D_80078EC8;
typedef struct {
    u8 pad[0x60]; s16 u60, u62, u64;
    u8 pad66[2]; s16 u68, u6A, u6C;
    u8 pad6E[2]; s16 u70, u72, u74;
    u8 pad76[0x80]; s16 uF6;
    u8 padF8[0x36]; s16 u12E;
    u8 pad130[0x88]; s16 u1B8, u1BA;
    u8 pad1BC[0xC]; s16 u1C8;
} T;
void func_80158AE4(T *p) {
    D_800AE6B0 = D_800AE6AC | 0x1000000;
    func_8016F264(p);
    func_80165840(p);
    func_801658DC(p);
    func_80165A20(p);
    func_80165A78(p);
    func_8014BF48();
    func_8014CBF8(p);
    func_8014B160(p);
    func_80149020(p);
    p->u12E = 0;
    p->u74 = 0x1000;
    p->u72 = 0x1000;
    p->u70 = 0x1000;
    p->u6C = 0x1000;
    p->u6A = 0x1000;
    p->u68 = 0x1000;
    p->u64 = 0x1000;
    p->u62 = 0x1000;
    p->u60 = 0x1000;
    p->u1BA = 0x1000;
    p->u1B8 = 0x1000;
    p->uF6 = 0x1000;
    D_80078EC8 = 0;
    p->u1C8 = 0;
    func_80146CA0(p);
}
