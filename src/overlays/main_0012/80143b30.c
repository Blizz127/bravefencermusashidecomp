/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FCA4[])(void *arg0);
extern s32 func_8012C658(s32 arg0, s32 arg1, void *arg2);

/* HAND MODEL of func_80143B30 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FCA4[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80143B30(u8 *arg0)
{
    D_8017FCA4[*(u16 *)(arg0 + 2)](arg0);
}

/* HAND MODEL of func_80143B6C (main_0012.s): s32 (u8 *, s32), 0x20
 * frame. v1 = 8012C658(0x1C, arg1, s0) (a2 = s0 is the jal delay
 * slot; arg1 passes through raw, unlike the sext'd 43994 use --
 * 12C658's prototype stays provisional). Zero v1, or a NULL
 * [s0+0x20], returns v1 at once (the addu delay slots); a nonzero
 * arg1 also returns v1; only arg1 == 0 with a live block copies
 * lhu(block+0x12) to [v1+0xFC] first. Callee decl provisional. */
s32 func_80143B6C(u8 *arg0, s32 arg1)
{
    u8 *s0 = arg0;
    u8 *a0;
    s32 v1 = func_8012C658(0x1C, arg1, s0);

    if (v1 == 0) {
        return 0;
    }
    a0 = *(u8 **)(s0 + 0x20);
    if (a0 == 0) {
        return v1;
    }
    if (arg1 == 0) {
        *(u16 *)((u8 *)v1 + 0xFC) = *(u16 *)(a0 + 0x12);
    }
    return v1;
}
