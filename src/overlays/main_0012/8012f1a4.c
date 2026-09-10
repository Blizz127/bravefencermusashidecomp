/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F1A4 (main_0012.s), decoded manually from
 * raw asm (0x70 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): calls 800484EC with
 * no arguments, then accumulates (arg0 words +0x14/+0x18/+0x1C
 * << 16) into arg2 words +0/+4/+8 (lw/sll/addu/sw). The middle
 * argument is never read (callers pass a scratch buffer); kept
 * as an explicit unused parameter. */

struct in_8012F1A4 {
    u8 pad[0x14];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct acc_8012F1A4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

extern void func_800484EC(void);

void func_8012F1A4(struct in_8012F1A4 *arg0, void *unused, struct acc_8012F1A4 *arg2) {
    (void) unused;
    func_800484EC();
    arg2->unk0 += arg0->unk14 << 16;
    arg2->unk4 += arg0->unk18 << 16;
    arg2->unk8 += arg0->unk1C << 16;
}
