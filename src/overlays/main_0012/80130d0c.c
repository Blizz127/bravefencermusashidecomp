/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80130D0C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dispatches through
 * D_8017E710[u8 arg0->unkC1] (word table; index 0 holds 0x80000,
 * handlers start at 1) via jalr with a nop delay slot, so both
 * live regs pass through. Modelled as a uniform 2-arg indirect
 * call: the table mixes 1-arg and 2-arg handlers, but on MIPS o32
 * the extra register is simply ignored by 1-arg targets, exactly
 * as retail. Returns the handler's v0 residue. Sole raw caller is
 * the 80178540 range (no hand model yet); it sets only a0. */

struct obj_80130D0C {
    u8 pad[0xC1];
    u8 unkC1;
};

typedef s32 (*handler_80130D0C)(void *arg0, s32 arg1);

extern handler_80130D0C D_8017E710[];

s32 func_80130D0C(struct obj_80130D0C *arg0, s32 arg1) {
    return D_8017E710[arg0->unkC1](arg0, arg1);
}
