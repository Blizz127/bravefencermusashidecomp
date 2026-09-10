/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80171A1C();
typedef struct {
    u8 pad[0x1F8]; s32 u1F8;
    s32 *u1FC;
    u8 pad200[0x14]; u8 u214;
} T;
void func_80171928(T *p) {
    p->u1F8 = p->u1FC[p->u214] | (p->u1F8 & 0x7F000000);
    func_80171A1C(p);
}
