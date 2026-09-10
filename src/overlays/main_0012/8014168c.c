/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

extern u8 D_80115148[];
extern u8 D_80115149[];
extern u8 D_80115158[];

/* HAND MODEL of func_8014168C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s32 (s32), leaf.
 * Returns sext(lbu(115148[i]) + lbu(115149[i])*lbu(115158[i]))
 * with i = sext(a0)*2 (the (a0<<16)>>15 shift pair). */
s32 func_8014168C(s32 arg0)
{
    s32 i = ((arg0 << 16) >> 16) * 2;

    return ((s32)(D_80115148[i] + D_80115149[i] * D_80115158[i]) << 16) >> 16;
}
