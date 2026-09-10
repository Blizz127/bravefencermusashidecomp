/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801719A4();
void func_80171B44();
void func_80171990();
void func_8016FC24();
typedef struct Inner { u8 pad[0x12]; u16 unk12; } Inner;
typedef struct {
    u8 pad[0x20]; Inner *inner;
    u8 pad24[0x10E]; u16 f132; u8 pad134[2]; s16 f136;
} T;
void func_8016FBB8(T *p) {
    p->f136 = 2;
    p->f132 = p->inner->unk12;
    p->inner->unk12 = (p->inner->unk12 + 0x800) & 0xFFF;
    func_801719A4(p, 1);
    func_80171B44(p);
    func_80171990(p);
    func_8016FC24(p);
}
