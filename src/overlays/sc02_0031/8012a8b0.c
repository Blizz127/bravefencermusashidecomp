/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012A8B0,8012A8E8).
 * Offset 0x2758 at overlay base 80128158. SHA256(span)=8ebc4b60cb7304d5d165ec959a700c60804a855de611b2cd873a4a2cecd38088.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012a8b0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820072)
MUSASHI_NATIVE_MIPS_WORD(0xAC850090)
MUSASHI_NATIVE_MIPS_WORD(0xAC800094)
MUSASHI_NATIVE_MIPS_WORD(0xAC80009C)
MUSASHI_NATIVE_MIPS_WORD(0xA480009A)
MUSASHI_NATIVE_MIPS_WORD(0x3042F9FF)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AAAB)
MUSASHI_NATIVE_MIPS_WORD(0xA4820072)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL from m2c draft of func_8012A8B0 (main_0012.s): NOT
 * verified against retail. C89-gated only; promotion requires an
 * oracle MATCH. Widths grounded from raw asm (sw/sw/sw/sh at 0x90/0x94/0x9C/0x9A, andi+sh at 0x72). Identical body to func_8012A828. */

struct obj_8012A828 {
    u8 pad[0x72];
    u16 unk72;
    u8 pad2[0x1C];
    s32 unk90;
    s32 unk94;
    s16 unk98;
    s16 unk9A;
    s32 unk9C;
};

void func_8012AAAC(void);

void func_8012A8B0(struct obj_8012A828 *arg0, s32 arg1) {
    arg0->unk90 = arg1;
    arg0->unk94 = 0;
    arg0->unk9C = 0;
    arg0->unk9A = 0;
    arg0->unk72 &= 0xF9FF;;
    func_8012AAAC();
}
#endif
