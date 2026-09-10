/* SC02 resident retail span [8014292C,80142978). Offset 0x1A7D4 at base 80128158.
 * SHA256(span)=4a1473f9f3de96c67f954501cfac7867d8fecc57522cbf055eb1bb6dbaf132f3.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017F7E4->D_801860D4.
 * Oracle MATCH re-earned against the resident image; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x846370C0)
MUSASHI_NATIVE_MIPS_WORD(0x24020003)
MUSASHI_NATIVE_MIPS_WORD(0x1062000A)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C2260D4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_801860D4[])(void *arg0);
extern void (*D_8017F9B4[])(void *arg0);
extern s16 D_801270C0;

/* HAND MODEL of func_8014292C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame (ra saved only on the taken path, via the beq delay slot).
 * Returns at once when lh(D_801270C0) == 3; otherwise indirect
 * tail-calls F7E4[lhu(a0+2)] with a0. Table element type
 * provisional. */
void func_8014292C(u8 *arg0)
{
    if (D_801270C0 == 3) {
        return;
    }
    D_801860D4[*(u16 *)(arg0 + 2)](arg0);
}

/* HAND MODEL of func_80142978 (main_0012.s): void (u8 *), 0x18
 * frame. Same shape through the F9B4 table. */
void func_80142978(u8 *arg0)
{
    if (D_801270C0 == 3) {
        return;
    }
    D_8017F9B4[*(u16 *)(arg0 + 2)](arg0);
}
#endif
