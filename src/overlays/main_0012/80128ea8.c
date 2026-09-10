/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80128EA8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): stores arg1->unk0
 * = arg2 (sw), u16 arg1->unk4 = 0 (sh), u16 arg1->unk6 =
 * *(s32 *)(arg2 + 4) & 0x3F (lw/andi/sh), u16 arg0->unk28 =
 * lhu(arg2 + 0), u16 arg0->unk2A = lhu(arg2 + 2) (the last in
 * the jr delay slot). */

struct obj_80128EA8 {
    void *unk0;
    u16 unk4;
    u16 unk6;
};

struct src_80128EA8 {
    u16 unk0;
    u16 unk2;
    s32 unk4;
};

struct dst_80128EA8 {
    u8 pad[0x28];
    u16 unk28;
    u16 unk2A;
};

void func_80128EA8(struct dst_80128EA8 *arg0, struct obj_80128EA8 *arg1, struct src_80128EA8 *arg2) {
    arg1->unk0 = arg2;
    arg1->unk4 = 0;
    arg1->unk6 = (u16) (arg2->unk4 & 0x3F);
    arg0->unk28 = arg2->unk0;
    arg0->unk2A = arg2->unk2;
}
