/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A1C();
void func_80174650();
typedef struct Inner { u8 pad[0x12]; u16 unk12; } Inner;
typedef struct {
    u8 pad[0x20];
    Inner *inner;
    u8 pad24[0x132-0x24];
    u16 f132;
    u8 pad134[2];
    s16 f136;
} T;
void func_80172ACC(T *p) {
    p->f136 = 0;
    p->inner->unk12 = p->f132;
    func_80171A1C(p);
    func_80174650(p);
}
