/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80137B80 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (void), 0x18
 * frame. D_80127548 = 0x24, then if (D_801269F0[0].w0 != 0)
 * func_80138BE0(&D_801269F0[0]) (a0 = base throughout, no a-reg
 * writes precede the jal), then D_8017E980++ (asm order: the
 * store precedes the call). Results ignored. Slot
 * view (0x4C stride, word 0) matches func_801379FC's; 38BE0 decl
 * likewise. */

struct slot_80137B80 {
    u32 w0;
    u8 pad[0x48];
};

extern struct slot_80137B80 D_801269F0[];
extern u32 D_80127548;
extern s32 D_8017E980;
extern void func_80138BE0(struct slot_80137B80 *arg0);

void func_80137B80(void) {
    D_80127548 = 0x24;
    if (D_801269F0[0].w0 != 0) {
        func_80138BE0(&D_801269F0[0]);
    }
    D_8017E980++;
}
