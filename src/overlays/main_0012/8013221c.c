/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_8013221C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): res = func_8012C1B8(arg0)
 * always stored to arg0+0x20 (delay slot, even NULL); NULL takes the
 * func_8012CAE4(arg0) path, else func_8001C214(res, 0), arg0+0x58 =
 * D_8017E8E0, arg0+0x5C = 0x80, arg0+0x2 += 1. Clone-twin of
 * func_801320D8/80132144/801321B0, verified from raw asm to differ
 * only in the table symbol. Same 8012C1B8 1-arg/pointer-out note as
 * func_80132018. */

struct obj_8013221C {
    u8 pad0[0x2];
    u16 unk2;
    u8 pad1[0x1C];
    s32 unk20;
    u8 pad2[0x34];
    void *unk58;
    u16 unk5C;
};

extern s32 func_8012C1B8(void *arg0);
extern void func_8012CAE4(void *arg0);
extern void func_8001C214(s32 arg0, s32 arg1);
extern u8 D_8017E8E0[];

void func_8013221C(struct obj_8013221C *arg0) {
    s32 res;

    res = func_8012C1B8(arg0);
    arg0->unk20 = res;
    if (res == 0) {
        func_8012CAE4(arg0);
        return;
    }
    func_8001C214(res, 0);
    arg0->unk58 = D_8017E8E0;
    arg0->unk5C = 0x80;
    arg0->unk2 = arg0->unk2 + 1;
}
