/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void (*D_8017FD14[])(void *arg0);
extern void *func_80010A08(s32 arg0);
extern void func_8004914C(void *arg0);
extern void func_800491AC(void *arg0);
extern s32 func_8004955C(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 func_8004787C(s32 arg0);
extern s32 func_80047948(s32 arg0);
extern void *D_800A651C[];
extern u16 D_800B9A02;
extern u8 D_800AF648[];

/* HAND MODEL of func_80144054 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FD14[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80144054(u8 *arg0)
{
    D_8017FD14[*(u16 *)(arg0 + 2)](arg0);
}
