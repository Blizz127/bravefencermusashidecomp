/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_801719A4();
void func_80171990();
void func_8016FB10();
typedef struct {
    u8 pad[0x20];
    u8 *inner;
    u8 pad24[0x132-0x24];
    u16 f132;
    u8 pad134[2];
    s16 f136;
} T;
void func_8016FAC0(T *p) {
    p->f136 = 2;
    p->f132 = *(u16 *)(p->inner + 0x12);
    func_801719A4(p, 2);
    func_80171990(p);
    func_8016FB10(p);
}
