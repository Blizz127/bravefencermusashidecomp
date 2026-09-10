/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FD2C[])(void *arg0);
extern void func_8012AD44(void *arg0, s32 arg1);

/* HAND MODEL of func_80144A2C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FD2C[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80144A2C(u8 *arg0)
{
    D_8017FD2C[*(u16 *)(arg0 + 2)](arg0);
}

/* HAND MODEL of func_80144A68 (main_0012.s): void (u8 *), 0x18
 * frame. Stores 0xC6 to [a0+0] in the 2AD44 jal delay slot
 * (before the call), then runs 8012AD44(a0, 0). (The trailing jr
 * ra pair is padding.) 2AD44 decl matches its 42838 use. */
void func_80144A68(u8 *arg0)
{
    *(u16 *)(arg0 + 0) = 0xC6;
    func_8012AD44(arg0, 0);
}
