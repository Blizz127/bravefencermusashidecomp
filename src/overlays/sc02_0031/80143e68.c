/* SC02.CD FILE_031 / ov_SC02_031 retail span [80143E68,80143EA4).
 * Offset 0x1BD10 at overlay base 80128158. SHA256(span)=eef1f0f82b37e0cc143d5261118f4c4691789b30f2e8b42393140153cbc466af.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017FD00 here is D_80180588 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C220588)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_80180588[])(void *arg0);

/* HAND MODEL of func_80143E68 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FD00[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * The three trailing jr ra pairs are padding. Table element type
 * provisional. */
void func_80143E68(u8 *arg0)
{
    D_80180588[*(u16 *)(arg0 + 2)](arg0);
}
#endif
