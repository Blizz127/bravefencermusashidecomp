/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80128FAC (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): calls
 * func_8001534C(4, &D_80182D20, 0x80, 0x90, 0, 0) (last two are
 * zero stack slots, second set in the jal delay slot), then
 * func_800153CC(5, lhu(arg0), 0xA8, 0x90, 0x40, 0) (0x40 stored
 * before the jal, final 0 in its delay slot). */

extern u8 D_80182D20;
extern void func_8001534C(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_800153CC(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_80182D20, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}
