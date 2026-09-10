/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80129C40 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): eight
 * func_80016714(ptr, 0xA4) calls over D_80126DB8, D_80126948,
 * D_80114EE8 (+0xA4/+0x148) and D_80126E60 (+0xA4/+0x148);
 * clears bytes D_801150D6, D_801152C0, D_80127504; calls
 * func_800144D4(). No incoming-arg use; returns void. */

extern u8 D_80126DB8;
extern u8 D_80126948;
extern u8 D_80114EE8;
extern u8 D_80126E60;
extern u8 D_801150D6;
extern u8 D_801152C0;
extern u8 D_80127504;
extern void func_80016714(void *arg0, s32 arg1);
extern void func_800144D4(void);

void func_80129C40(void) {
    u8 *s0;

    func_80016714(&D_80126DB8, 0xA4);
    func_80016714(&D_80126948, 0xA4);
    s0 = &D_80114EE8;
    func_80016714(s0, 0xA4);
    func_80016714(s0 + 0xA4, 0xA4);
    func_80016714(s0 + 0x148, 0xA4);
    s0 = &D_80126E60;
    func_80016714(s0, 0xA4);
    func_80016714(s0 + 0xA4, 0xA4);
    func_80016714(s0 + 0x148, 0xA4);
    D_801150D6 = 0;
    D_801152C0 = 0;
    D_80127504 = 0;
    func_800144D4();
}
