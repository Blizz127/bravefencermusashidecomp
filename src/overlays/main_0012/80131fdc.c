/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80131FDC (main_0012.s), decoded manually from raw
 * asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): indirect tail
 * dispatcher, 0x18 frame, s32 result. Calls the code pointer at
 * D_8017E908[(u16)arg0[1]] (lhu + sll-2 + lw) via jalr with a0 still
 * live (no a-reg writes precede it) and returns its . Table
 * contents unstaged; the s32(void*)-typed view matches the
 * func_80042580 callback precedent. */

struct h_80131FDC {
    u16 unk0;
    u16 unk2;
};

typedef s32 (*tgt_80131FDC)(struct h_80131FDC *);

extern tgt_80131FDC D_8017E908[];

s32 func_80131FDC(struct h_80131FDC *arg0) {
    return D_8017E908[arg0->unk2](arg0);
}
