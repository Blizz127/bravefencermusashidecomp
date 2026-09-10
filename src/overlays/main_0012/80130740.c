/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80130740 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): calls
 * func_80146A6C(0x10, arg0, (s16)(arg0[3]+arg1[0]),
 * (s16)(arg0[5]+arg1[1]), (s16)(arg0[7]+arg1[2]), 0, 0) (u16
 * triplet sums with sll/sra half-sign-extend; the first stack word
 * is stored in the jal delay slot, the other two are pre-zeroed).
 * Returns void. */

extern void func_80146A6C(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6);

void func_80130740(u16 *arg0, u16 *arg1) {
    func_80146A6C(0x10, arg0, (s16)(arg0[3] + arg1[0]), (s16)(arg0[5] + arg1[1]), (s16)(arg0[7] + arg1[2]), 0, 0);
}
