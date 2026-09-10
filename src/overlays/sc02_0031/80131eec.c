/* SC02 resident retail span [80131EEC,80131F28). Offset 0x9D94 at base 80128158.
 * SHA256(span)=2eb44c06f60955d6a59135c3f089364d414954f98436ac6a9d5e818cc73859f6.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017E8A8->D_80185198.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C225198)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80131EEC (main_0012.s), decoded manually from raw
 * asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): indirect tail
 * dispatcher, 0x18 frame, s32 result. Calls the code pointer at
 * D_80185198[(u16)arg0[1]] (lhu + sll-2 + lw) via jalr with a0 still
 * live (no a-reg writes precede it) and returns its . Table
 * contents unstaged; the s32(void*)-typed view matches the
 * func_80042580 callback precedent. */

struct h_80131EEC {
    u16 unk0;
    u16 unk2;
};

typedef s32 (*tgt_80131EEC)(struct h_80131EEC *);

extern tgt_80131EEC D_80185198[];

s32 func_80131EEC(struct h_80131EEC *arg0) {
    return D_80185198[arg0->unk2](arg0);
}
#endif
