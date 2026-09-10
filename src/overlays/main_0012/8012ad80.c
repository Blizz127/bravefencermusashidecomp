/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012AD80 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All accesses grounded as lw/sw/addu words from raw asm; order matches m2c exactly. */

struct obj_8012AD80 {
    u8 pad[4];
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x28];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

void func_8012AD80(struct obj_8012AD80 *arg0) {
    arg0->unk10 = arg0->unk10 + arg0->unk44;
    arg0->unk14 = arg0->unk14 + arg0->unk48;
    arg0->unk18 = arg0->unk18 + arg0->unk4C;
    arg0->unk4 = arg0->unk4 + arg0->unk10;
    arg0->unk8 = arg0->unk8 + arg0->unk14;
    arg0->unkC = arg0->unkC + arg0->unk18;
}

