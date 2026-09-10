/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_801307B0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s0->unkC1 = 0x10;
 * s0->unk5C = 0 (jal delay slot, lands before the call);
 * func_801312D0(s0, buf) fills 3 u16 halves; then
 * func_80146A6C(0x10, s0, (s16)(s0->unk6 + buf[0]),
 * (s16)(s0->unkA + buf[1]), (s16)(s0->unkE + buf[2]), 0, 0)
 * (first stack word in the jal delay slot, others pre-zeroed);
 * s0->unk1C = 0x1E; s0->unk18 = 0; s0->unk10 = 0 (jal delay slot);
 * func_8002D4C8(0x531, 0). Returns void. */

struct obj_801307B0 {
    u8 pad[0x6];
    u16 unk6;
    u16 pad6;
    u16 unkA;
    u16 padA;
    u16 unkE;
    s32 unk10;
    u8 pad2[0x18 - 0x14];
    s32 unk18;
    s32 unk1C;
    u8 pad3[0x5C - 0x20];
    u16 unk5C;
    u8 pad4[0xC1 - 0x5E];
    u8 unkC1;
};

extern void func_801312D0(void *arg0, u16 *arg1);
extern void func_80146A6C(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_801307B0(struct obj_801307B0 *arg0) {
    u16 buf[4];

    arg0->unkC1 = 0x10;
    arg0->unk5C = 0;
    func_801312D0(arg0, buf);
    func_80146A6C(0x10, arg0, (s16)(arg0->unk6 + buf[0]), (s16)(arg0->unkA + buf[1]), (s16)(arg0->unkE + buf[2]), 0, 0);
    arg0->unk1C = 0x1E;
    arg0->unk18 = 0;
    arg0->unk10 = 0;
    func_8002D4C8(0x531, 0);
}
