/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80154A74();
void func_801553C0();
void func_801470AC();
void func_801472B4();
void func_801477E8();
void func_80153C18();
typedef struct Inner { u8 pad[0x10]; s16 unk10; } Inner;
typedef struct {
    u8 pad[0x20];
    Inner *inner;
    u8 pad24[0x18];
    u16 f3C, f3E, f40, f42;
    u8 pad44[0x1C];
    s16 f60, f62, f64;
    u8 pad66[0xDD-0x66];
    u8 fDD;
} T;
void func_80151664(T *p) {
    func_80154A74(p, 0x11);
    func_801553C0(p);
    func_801470AC(p);
    func_801472B4(p);
    p->f3E = 0;
    p->f40 = 0;
    p->f42 = 0;
    p->fDD = 0;
    p->f3C &= 0xFFFE;
    p->inner->unk10 = 0;
    p->f60 = 0x1000;
    p->f62 = 0x1000;
    p->f64 = 0x1000;
    func_801477E8(p, 0);
    func_80153C18(p);
}
