/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E22C,8013E298).
 * Offset 0x160D4 at overlay base 80128158. SHA256(span)=32cf9632f14fb7a86368fd2ca8d976a0e6605926fe4af1e7a01995e189c90c39.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e22c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFC8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x84A30000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0x84820006)
MUSASHI_NATIVE_MIPS_WORD(0x84A30002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20014)
MUSASHI_NATIVE_MIPS_WORD(0x8482000A)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0x84A30004)
MUSASHI_NATIVE_MIPS_WORD(0x27A50020)
MUSASHI_NATIVE_MIPS_WORD(0x00431023)
MUSASHI_NATIVE_MIPS_WORD(0x0C0124BF)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20020)
MUSASHI_NATIVE_MIPS_WORD(0x8FA30024)
MUSASHI_NATIVE_MIPS_WORD(0x8FA40028)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0030)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0038)
#else
#include "psx_types.h"

extern void func_800492FC(s32 *arg0, s32 *arg1);

/* HAND MODEL of func_8013E22C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): u32 (s16 *, s16 *),
 * 0x38 frame. Integer sibling of the BLOCKED sqr trio (same
 * staggered half pairing as func_8013E0FC: arg0[1,3,5] minus
 * arg1[0,1,2], subu): spills the three diffs to the stack (the
 * third rides the jal delay slot, so it lands before the callee
 * runs), calls func_800492FC(diffs, out) (provisional decl), and
 * returns out[0] + out[1] + out[2] (addu wrap). */
u32 func_8013E22C(s16 *arg0, s16 *arg1)
{
    s32 diffs[3];
    s32 out[3];

    diffs[0] = (s32)arg0[1] - (s32)arg1[0];
    diffs[1] = (s32)arg0[3] - (s32)arg1[1];
    diffs[2] = (s32)arg0[5] - (s32)arg1[2];
    func_800492FC(diffs, out);
    return (u32)out[0] + (u32)out[1] + (u32)out[2];
}
#endif
