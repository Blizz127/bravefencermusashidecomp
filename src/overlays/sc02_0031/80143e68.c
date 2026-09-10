/* SC02 resident retail span [80143E68,80143EA4). Offset 0x1BD10 at base 80128158.
 * SHA256(span)=8f1008a39ed4ec4c18ff7d25b8169884dc0fa812de29cf260e9c75a03cf35373.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017FD00->D_801865F0.
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
MUSASHI_NATIVE_MIPS_WORD(0x8C2265F0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_801865F0[])(void *arg0);

/* HAND MODEL of func_80143E68 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FD00[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * The three trailing jr ra pairs are padding. Table element type
 * provisional. */
void func_80143E68(u8 *arg0)
{
    D_801865F0[*(u16 *)(arg0 + 2)](arg0);
}
#endif
