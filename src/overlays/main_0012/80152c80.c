/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8014BC44();
void func_80154A74();
void func_801553C0();
void func_801470AC();
void func_801472B4();
void func_801477E8();
void func_80153C18();
typedef struct Inner { u8 pad[0x10]; s16 u10; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x18]; u16 u3C, u3E, u40, u42;
    u8 pad44[0x1C]; s16 u60, u62, u64;
    u8 pad66[0x42]; u8 uA8;
    u8 padA9[0x34]; u8 uDD;
    u8 padDE[0x14]; s16 uF2;
} T;
void func_80152C80(T *p) {
    func_8014BC44(p, p->uF2);
    p->uA8 = 0x20;
    func_80154A74(p, 0x11);
    func_801553C0(p);
    func_801470AC(p);
    func_801472B4(p);
    p->u3E = 0;
    p->u40 = 0;
    p->u42 = 0;
    p->uDD = 0;
    p->u3C &= 0xFFFE;
    p->inner->u10 = 0;
    p->u60 = 0x1000;
    p->u62 = 0x1000;
    p->u64 = 0x1000;
    func_801477E8(p, 0);
    func_80153C18(p);
}
