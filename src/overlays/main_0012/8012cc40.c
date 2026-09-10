/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012CC40 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Passthrough wrapper: object in a0, incoming a1 to a2, mode 1 in the delay slot. */

struct obj_8012CC88 {
    u8 pad[4];
    s32 unk4;
    u16 unk6;
    s32 unk8;
    u16 unkA;
    s32 unkC;
    u16 unkE;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 pad2[0x1E];
    u16 unk3A;
    u16 pad3;
    u16 unk3E;
    u16 pad4;
    u16 unk42;
    s32 unk44;
    s32 unk48;
    s32 unk4C;
};

extern u16 D_800D3918[];

void func_8012CC88(struct obj_8012CC88 *arg0, s32 arg1, u16 *arg2);

void func_8012CC40(struct obj_8012CC88 *arg0, u16 *arg1) {
    func_8012CC88(arg0, 1, arg1);
}

