/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FCB8[])(void *arg0);
extern s32 func_8012C658(s32 arg0, s32 arg1, void *arg2);

/* HAND MODEL of func_80143C98 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FCB8[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80143C98(u8 *arg0)
{
    D_8017FCB8[*(u16 *)(arg0 + 2)](arg0);
}

/* HAND MODEL of func_80143CD4 (main_0012.s): void (u8 *), 0x18
 * frame. Issues 8012C658(0x39, k, s0) for k = 0, 1, 2 (a2 = s0
 * rides each jal delay slot), discarding all three results.
 * 12C658 decl matches its 43994/43B6C/43C74 uses. */
void func_80143CD4(u8 *arg0)
{
    func_8012C658(0x39, 0, arg0);
    func_8012C658(0x39, 1, arg0);
    func_8012C658(0x39, 2, arg0);
}
