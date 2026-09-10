/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_8012AD80(void *arg0);
extern s32 func_80128ED8(void *arg0, void *arg1);
extern void func_80016714(void *arg0, s32 arg1);
extern void func_8012C218(void *arg0);

/* HAND MODEL of func_8014462C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x20
 * frame. Runs 8012AD80(s0) first (a0 still holds s0 across the nop
 * delay slot; staged single-pointer shape, used verbatim), copies
 * lhu(s0+6/0xA/0xE) to [s1+8/0xA/0xC] (s1 = [s0+0xCC]; the last in
 * the 28ED8 jal delay slot) and runs 80128ED8(s1, s0+0xD0);
 * nonzero runs 80016714(s1, 0x38) then 8012C218(s0) (a0
 * pre-pointed in each jal delay slot). Callee decls provisional
 * except the staged 2AD80 shape. */
void func_8014462C(u8 *arg0)
{
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0xCC);
    s32 v0;

    func_8012AD80(s0);
    *(u16 *)(s1 + 8) = *(u16 *)(s0 + 6);
    *(u16 *)(s1 + 0xA) = *(u16 *)(s0 + 0xA);
    *(u16 *)(s1 + 0xC) = *(u16 *)(s0 + 0xE);
    v0 = func_80128ED8(s1, s0 + 0xD0);
    if (v0 != 0) {
        func_80016714(s1, 0x38);
        func_8012C218(s0);
    }
}
