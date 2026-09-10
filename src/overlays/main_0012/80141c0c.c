/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern u16 D_80115110;
extern u16 D_8017F6D4[];

/* HAND MODEL of func_80141C0C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32), 0x18
 * frame. Runs 8002D4C8(lhu(F6D4[sext(a0)*2 + lhu(115110)]), 0)
 * (the (a0<<16)>>15 pair is sext(a0)*2; the final <<1 makes it a
 * byte offset = u16 element index). 2D4C8 decl matches the
 * provisional (s32, s32) shape used verbatim across staging. */
void func_80141C0C(s32 arg0)
{
    func_8002D4C8(D_8017F6D4[((arg0 << 16) >> 16) * 2 + D_80115110], 0);
}
