/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012F038 (main_0012.s), decoded manually from
 * raw asm (0x84 bytes; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): builds an s32 triple
 * of (s16)arg1[0/2/4] - (s32)arg0[0x14/0x18/0x1C] (lh/lw/subu),
 * runs func_8004D504(arg0, in, out) (a0 passes through: the jal
 * sets only a1/a2, verified against raw; m2c dropped it), and stores the three result words
 * as halfwords to out[0/2/4] (lw/sh). */

struct in_8012F038 {
    u8 pad[0x14];
    s32 unk14;
    s32 unk18;
    s32 unk1C;
};

struct u16in_8012F038 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

struct out_8012F038 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
};

extern void func_8004D504(void *arg0, s32 *arg1, s32 *arg2);

void func_8012F038(struct in_8012F038 *arg0, struct u16in_8012F038 *arg1, struct out_8012F038 *arg2) {
    s32 in[3];
    s32 out[3];

    in[0] = arg1->unk0 - arg0->unk14;
    in[1] = arg1->unk2 - arg0->unk18;
    in[2] = arg1->unk4 - arg0->unk1C;
    func_8004D504(arg0, in, out);
    arg2->unk0 = (s16) out[0];
    arg2->unk2 = (s16) out[1];
    arg2->unk4 = (s16) out[2];
}
