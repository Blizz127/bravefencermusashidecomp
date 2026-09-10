/* SC02.CD FILE_031 / ov_SC02_031 retail span [80143C98,80143CD4).
 * Offset 0x1BB40 at overlay base 80128158. SHA256(span)=6eda7ef9bbba61b6b63340bdbd447117157ed2ddf5dbef4222399b3352a222c1.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017FCB8 here is D_80180540 (+0x888 member
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
MUSASHI_NATIVE_MIPS_WORD(0x8C220540)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void (*D_80180540[])(void *arg0);
extern s32 func_8012C658(s32 arg0, s32 arg1, void *arg2);

/* HAND MODEL of func_80143C98 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (u8 *), 0x18
 * frame. Indirect tail-call of FCB8[lhu(a0+2)] with a0 (which
 * still holds the incoming pointer across the nop delay slot).
 * Table element type provisional. */
void func_80143C98(u8 *arg0)
{
    D_80180540[*(u16 *)(arg0 + 2)](arg0);
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
