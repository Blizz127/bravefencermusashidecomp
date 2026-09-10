/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern void *func_8012C588(s32 arg0, s32 arg1);

/* HAND MODEL of func_80142414 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32, s32),
 * 0x18 frame. Runs 8012C588(0x13, arg0) and, when its result is
 * nonzero, stores arg0's low half to result+0x52. Callee decl
 * provisional. */
void func_80142414(s32 arg0, s32 arg1)
{
    u8 *v0 = (u8 *)func_8012C588(0x13, arg0);

    if (v0 != 0) {
        *(u16 *)(v0 + 0x52) = (u16)arg1;
    }
}
