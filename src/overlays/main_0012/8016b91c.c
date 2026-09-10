/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_8016B964();
void func_8016B964();
void func_8016B964();
typedef struct {
    u8 pad_0[16];
    s32 f10;
    s32 f14;
    s32 f18;
} T;
void func_8016B91C(T *p) {
    func_8016B964(p, p->f10);
    func_8016B964(p, p->f14);
    func_8016B964(p, p->f18);
}
