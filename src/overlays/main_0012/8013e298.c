/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern s16 D_80126CB0;

/* HAND MODEL of func_8013E298 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): u32 (s16 *),
 * frameless O2 leaf. Returns |arg0[2] - D_80126CB0| - 0x2C1 < 0x3F
 * (negu absolute value, addiu -0x2C1, sltiu boolean riding the jr
 * delay slot). s16 decl mirrors staging/hand/func_8012BF7C.c. */
u32 func_8013E298(s16 *arg0)
{
    s32 v0;

    v0 = (s32)arg0[2] - (s32)D_80126CB0;
    if (v0 < 0) {
        v0 = -v0;
    }
    v0 -= 0x2C1;
    return (u32)v0 < 0x3F;
}
