/* SC02.CD FILE_031 / ov_SC02_031 retail span [80138BE0,80138C30).
 * Offset 0x10A88 at overlay base 80128158. SHA256(span)=feed1eacc86581b89056b14ec4fe7ba92294362bd5b6dab956832c2b94a509f6.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017E984 here is D_8017F20C (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x9482000E)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xA482000E)
MUSASHI_NATIVE_MIPS_WORD(0x84820004)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22F20C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80138BE0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): s32 result, 0x18
 * frame. If (h0E != 0) h0E--; then tail-dispatch
 * D_8017F20C[lh(h04)] via jalr with a0 still live (no a-reg
 * writes precede it), returning the target's $v0. Callers
 * ignore the result; the s32 is forwarded for machine
 * exactness. Table contents unstaged; the s32(struct*)-typed
 * view matches the indirect-dispatcher precedent. */

struct h_80138BE0 {
    u8 pad00[4];
    s16 h04;
    u8 pad06[8];
    u16 h0E;
};

typedef s32 (*tgt_80138BE0)(struct h_80138BE0 *);

extern tgt_80138BE0 D_8017F20C[];

s32 func_80138BE0(struct h_80138BE0 *arg0) {
    if (arg0->h0E != 0) {
        arg0->h0E--;
    }
    return D_8017F20C[arg0->h04](arg0);
}
#endif
