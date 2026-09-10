/* SC02 resident retail span [80138BE0,80138C30). Offset 0x10A88 at base 80128158.
 * SHA256(span)=6cfd046113b4190098db3f315bc54e4009a2ddda3f28d69b417756f063df7305.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017E984->D_80185274.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
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
MUSASHI_NATIVE_MIPS_WORD(0x8C225274)
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
 * D_80185274[lh(h04)] via jalr with a0 still live (no a-reg
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

extern tgt_80138BE0 D_80185274[];

s32 func_80138BE0(struct h_80138BE0 *arg0) {
    if (arg0->h0E != 0) {
        arg0->h0E--;
    }
    return D_80185274[arg0->h04](arg0);
}
#endif
