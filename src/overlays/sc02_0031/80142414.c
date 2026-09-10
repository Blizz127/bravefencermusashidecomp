/* SC02.CD FILE_031 / ov_SC02_031 retail span [80142414,80142454).
 * Offset 0x1A2BC at overlay base 80128158. SHA256(span)=9dab4606ac508291ee887be5155a0948d70723ab614547a19c942f3cb4e2bc31.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80142414.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00A08021)
MUSASHI_NATIVE_MIPS_WORD(0x24040013)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B162)
MUSASHI_NATIVE_MIPS_WORD(0x00402821)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA4500052)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern void *func_8012C588(s32 arg0, s32 arg1);

/* HAND MODEL of func_80142414 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): void (s32, s32),
 * 0x18 frame. Runs 8012C588(0x13, arg0) and, when its result is
 * nonzero, stores arg0's low half to result+0x52. Callee decl
 * provisional. */
void func_80142414(s32 arg0, s32 arg1)
{
    u8 *v0 = (u8 *)func_8012C588(0x13, arg0);

    if (v0 != 0) {
        *(u16 *)(v0 + 0x52) = (u16)arg1;
    }
}
#endif
