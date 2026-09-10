/* SC02 resident retail span [801429C4,80142A10). Offset 0x1A86C at base 80128158.
 * SHA256(span)=55b1e346187496962bba1b22e05d01fa68fbf479f9d72d78e5dc4aff87979d52.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017FA6C->D_8018635C.
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
MUSASHI_NATIVE_MIPS_WORD(0x8C22635C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_8018635C[])(void *arg0);
extern s16 D_801270C0;

/* HAND MODEL of func_801429C4 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame (ra saved only on the taken path, via the beq delay slot).
 * Returns at once when lh(D_801270C0) == 3; otherwise indirect
 * tail-calls FA6C[lhu(a0+2)] with a0. Table element type
 * provisional. */
void func_801429C4(u8 *arg0)
{
    if (D_801270C0 == 3) {
        return;
    }
    D_8018635C[*(u16 *)(arg0 + 2)](arg0);
}
#endif
