/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_800492FC(s32 *arg0, s32 *arg1);

/* HAND MODEL of func_8013E22C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): u32 (s16 *, s16 *),
 * 0x38 frame. Integer sibling of the BLOCKED sqr trio (same
 * staggered half pairing as func_8013E0FC: arg0[1,3,5] minus
 * arg1[0,1,2], subu): spills the three diffs to the stack (the
 * third rides the jal delay slot, so it lands before the callee
 * runs), calls func_800492FC(diffs, out) (provisional decl), and
 * returns out[0] + out[1] + out[2] (addu wrap). */
u32 func_8013E22C(s16 *arg0, s16 *arg1)
{
    s32 diffs[3];
    s32 out[3];

    diffs[0] = (s32)arg0[1] - (s32)arg1[0];
    diffs[1] = (s32)arg0[3] - (s32)arg1[1];
    diffs[2] = (s32)arg0[5] - (s32)arg1[2];
    func_800492FC(diffs, out);
    return (u32)out[0] + (u32)out[1] + (u32)out[2];
}
