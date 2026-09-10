/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F0BC (main_0012.s), decoded manually from
 * raw asm (0x90 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): sibling of
 * func_8012F038 with word inputs: builds an s32 triple of
 * arg1[0/4/8] - (arg0[0x14/0x18/0x1C] << 16) (lw/sll/subu),
 * runs func_8004D504(arg0, in, out) (a0 passes through: the jal
 * sets only a1/a2, verified against raw; m2c dropped it), and stores the three result words
 * to out[0/4/8] (sw). */

struct in_8012F0BC {
    u8 pad[0x14];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct win_8012F0BC {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct wout_8012F0BC {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F0BC(struct in_8012F0BC *arg0, struct win_8012F0BC *arg1, struct wout_8012F0BC *arg2) {
    s32 in[3];
    s32 out[3];

    in[0] = arg1->unk0 - (arg0->unk14 << 16);
    in[1] = arg1->unk4 - (arg0->unk18 << 16);
    in[2] = arg1->unk8 - (arg0->unk1C << 16);
    func_8004D504(arg0, in, out);
    arg2->unk0 = out[0];
    arg2->unk4 = out[1];
    arg2->unk8 = out[2];
}
