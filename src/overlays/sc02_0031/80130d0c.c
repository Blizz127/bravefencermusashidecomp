/* SC02 resident retail span [80130D0C,80130D48). Offset 0x8BB4 at base 80128158.
 * SHA256(span)=6b945002f7550b7b2b93e750b56b292636aa116d21c0ae456aa608e8da6ca503.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017E710->D_80185000.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x908200C1)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C225000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_80130D0C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): dispatches through
 * D_80185000[u8 arg0->unkC1] (word table; index 0 holds 0x80000,
 * handlers start at 1) via jalr with a nop delay slot, so both
 * live regs pass through. Modelled as a uniform 2-arg indirect
 * call: the table mixes 1-arg and 2-arg handlers, but on MIPS o32
 * the extra register is simply ignored by 1-arg targets, exactly
 * as retail. Returns the handler's v0 residue. Sole raw caller is
 * the 80178540 range (no hand model yet); it sets only a0. */

struct obj_80130D0C {
    u8 pad[0xC1];
    u8 unkC1;
};

typedef s32 (*handler_80130D0C)(void *arg0, s32 arg1);

extern handler_80130D0C D_80185000[];

s32 func_80130D0C(struct obj_80130D0C *arg0, s32 arg1) {
    return D_80185000[arg0->unkC1](arg0, arg1);
}
#endif
