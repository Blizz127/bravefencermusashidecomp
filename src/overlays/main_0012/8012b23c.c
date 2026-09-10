/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012B23C (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. All stores grounded as sw; unk48 = 0x18000 via lui/ori. */

struct obj_8012B200 {
    u8 pad[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x28];
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

void func_8012B23C(struct obj_8012B200 *arg0) {
    arg0->unk18 = 0;
    arg0->unk14 = 0;
    arg0->unk10 = 0;
    arg0->unk4C = 0;
    arg0->unk44 = 0;
    arg0->unk48 = 0x18000;
}

