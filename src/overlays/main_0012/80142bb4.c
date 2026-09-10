/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_801439C0(void *arg0);
extern void func_8012AD44(void *arg0, s32 arg1);
extern void func_8012C218(void *arg0);
extern void func_8012C098(void *arg0);

/* HAND MODEL of func_80142BB4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *, s32,
 * s32), 0x20 frame. s1 = a2 via the first bne delay slot. When
 * lh(s0+0xFC) == 1: a nonzero a1, or a zero lh(s0+0x100), takes
 * the 42BF0 path (mask lhu(s0+0x5C) &= ~0x101, set bit 31 of
 * [[s0+0x20]+4], run 801439C0([s0+0xCC]), then 8012AD44(s0,
 * sext(s1))); otherwise returns via 42C64. When != 1: a nonzero
 * a1 or a zero lh(s0+0x100) runs 8012C218(s0), else 8012C098(s0);
 * both join 42C64. Callee decls provisional. */
void func_80142BB4(u8 *arg0, s32 arg1, s32 arg2)
{
    u8 *s0 = arg0;
    s32 s1 = arg2;

    if (*(s16 *)(s0 + 0xFC) == 1) {
        if (arg1 == 0 && *(s16 *)(s0 + 0x100) != 0) {
            return;
        }
        *(u16 *)(s0 + 0x5C) = (u16)(*(u16 *)(s0 + 0x5C) & 0xFEFE);
        *(u32 *)(*(u8 **)(s0 + 0x20) + 4) |= 0x80000000;
        func_801439C0(*(void **)(s0 + 0xCC));
        func_8012AD44(s0, (s1 << 16) >> 16);
        return;
    }
    if (arg1 != 0 || *(s16 *)(s0 + 0x100) == 0) {
        func_8012C218(s0);
        return;
    }
    func_8012C098(s0);
}

/* HAND MODEL of func_80142C84 (main_0012.s): void (u8 *), leaf.
 * Stores 0xFFF40000 to a0+0x14, 0x20000 to a0+0x48, and zero to
 * a0+0x102 (the sh is the jr delay slot, i.e. before the
 * return). */
void func_80142C84(u8 *arg0)
{
    *(u32 *)(arg0 + 0x14) = 0xFFF40000;
    *(u32 *)(arg0 + 0x48) = 0x20000;
    *(u16 *)(arg0 + 0x102) = 0;
}
