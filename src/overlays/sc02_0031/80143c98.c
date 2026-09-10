/* SC02 resident retail span [80143C98,80143CD4). Offset 0x1BB40 at base 80128158.
 * SHA256(span)=9d547e592b5bff864f8c1412625d2636355b480071a907c5dd8bf1a1d7df188a.
 * Words are the guest's loaded image (artifacts/sc02-resident-20260910).
 * Member-0012 C shape retargeted to this member: D_8017FCB8->D_801865A8.
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
MUSASHI_NATIVE_MIPS_WORD(0x8C2265A8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_801865A8[])(void *arg0);
extern s32 func_8012C658(s32 arg0, s32 arg1, void *arg2);

/* HAND MODEL of func_80143C98 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FCB8[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80143C98(u8 *arg0)
{
    D_801865A8[*(u16 *)(arg0 + 2)](arg0);
}

/* HAND MODEL of func_80143CD4 (main_0012.s): void (u8 *), 0x18
 * frame. Issues 8012C658(0x39, k, s0) for k = 0, 1, 2 (a2 = s0
 * rides each jal delay slot), discarding all three results.
 * 12C658 decl matches its 43994/43B6C/43C74 uses. */
void func_80143CD4(u8 *arg0)
{
    func_8012C658(0x39, 0, arg0);
    func_8012C658(0x39, 1, arg0);
    func_8012C658(0x39, 2, arg0);
}
#endif
