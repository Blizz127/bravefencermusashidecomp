/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

/* HAND MODEL of func_80138DB8 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s32 (void *,
 * s32, s32), 0x18 frame. Incoming a0 is discarded (andi
 * targets a0); 14E80(a1 & 0xFF, a2) (a1 = a2 rides the jal
 * delay slot); return (s32)(s16)ret (sll-16 + sra-16
 * sign-extends the low half). The s32 is observed by
 * func_80139F14 (low-half test); this also confirms that
 * file's 3-reg decl (dead a0 first). 14E80 decl mirrored
 * s32 2-arg (staged shape). Six overlay callers (four in
 * the 389xx dispatch cluster, 39F14, one ahead); the s32
 * serves users and ignorers alike. */

extern s32 func_80014E80(s32 arg0, s32 arg1);

s32 func_80138DB8(void *arg0, s32 arg1, s32 arg2) {
    (void)arg0;
    return (s32)(s16)func_80014E80(arg1 & 0xFF, arg2);
}
