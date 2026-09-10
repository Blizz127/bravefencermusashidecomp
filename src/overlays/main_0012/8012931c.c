/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8012931C (main_0012.s), decoded manually from
 * raw asm (fully visible, no frame; NOT verified against retail;
 * C89-gated only, promotion requires an oracle MATCH):
 * accumulates three word pairs: unk4 += unk10, unk8 += unk14,
 * unkC += unk18 (lw/addu/sw; the unkC store sits in the jr
 * delay slot). */

struct obj_8012931C {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
};

void func_8012931C(struct obj_8012931C *arg0) {
    arg0->unk4 += arg0->unk10;
    arg0->unk8 += arg0->unk14;
    arg0->unkC += arg0->unk18;
}
