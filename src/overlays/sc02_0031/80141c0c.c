/* SC02.CD FILE_031 / ov_SC02_031 retail span [80141C0C,80141C50).
 * Offset 0x19AB4 at overlay base 80128158. SHA256(span)=72495eb128a55f845cacdbe20f92b66479d6df2e9856da15c7b3e5e00b3cc406.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017F6D4 here is D_8017FF5C (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00042400)
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x94425110)
MUSASHI_NATIVE_MIPS_WORD(0x000423C3)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x00042040)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00240821)
MUSASHI_NATIVE_MIPS_WORD(0x9424FF5C)
MUSASHI_NATIVE_MIPS_WORD(0x0C00B532)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void func_8002D4C8(s32 arg0, s32 arg1);
extern u16 D_80115110;
extern u16 D_8017FF5C[];

/* HAND MODEL of func_80141C0C (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32), 0x18
 * frame. Runs 8002D4C8(lhu(F6D4[sext(a0)*2 + lhu(115110)]), 0)
 * (the (a0<<16)>>15 pair is sext(a0)*2; the final <<1 makes it a
 * byte offset = u16 element index). 2D4C8 decl matches the
 * provisional (s32, s32) shape used verbatim across staging. */
void func_80141C0C(s32 arg0)
{
    func_8002D4C8(D_8017FF5C[((arg0 << 16) >> 16) * 2 + D_80115110], 0);
}
#endif
