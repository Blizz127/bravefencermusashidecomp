/* SC02.CD FILE_031 / ov_SC02_031 retail span [80130D0C,80130D48).
 * Offset 0x8BB4 at overlay base 80128158. SHA256(span)=086545abbcff389b44af7cb04fdd299ac4c27970ed17c495547903f89bacb690.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017E710 here is D_8017EF98 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x908200C1)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22EF98)
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
 * D_8017EF98[u8 arg0->unkC1] (word table; index 0 holds 0x80000,
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

extern handler_80130D0C D_8017EF98[];

s32 func_80130D0C(struct obj_80130D0C *arg0, s32 arg1) {
    return D_8017EF98[arg0->unkC1](arg0, arg1);
}
#endif
