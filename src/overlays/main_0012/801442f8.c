/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FD1C[])(void *arg0);
extern void func_8012C218(void *arg0);

/* HAND MODEL of func_801442F8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect-calls FD1C[lhu(s0+2)] with s0 (a0 still holds it
 * across the nop delay slot), bumps [s0+0x1C], and runs
 * 8012C218(s0) (a0 pre-pointed in the jal delay slot) unless the
 * bumped value is still below 0x1E. Table element type and callee
 * decl provisional (12C218's shape matches its 42608 use). */
void func_801442F8(u8 *arg0)
{
    u8 *s0 = arg0;
    u32 v0;

    D_8017FD1C[*(u16 *)(s0 + 2)](s0);
    v0 = *(u32 *)(s0 + 0x1C) + 1;
    *(u32 *)(s0 + 0x1C) = v0;
    if ((s32)v0 >= 0x1E) {
        func_8012C218(s0);
    }
}
