/* SC02.CD FILE_031 / ov_SC02_031 retail span [80138DB8,80138DE0).
 * Offset 0x10C60 at overlay base 80128158. SHA256(span)=4cd337d7032d0927c5d0ce6c0ed1a37c8e728ccaef24f387958a322077751e7d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80138db8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x30A400FF)
MUSASHI_NATIVE_MIPS_WORD(0x0C0053A0)
MUSASHI_NATIVE_MIPS_WORD(0x00C02821)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
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
#endif
