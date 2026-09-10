/* SC02.CD FILE_031 / ov_SC02_031 retail span [801303A0,801303EC).
 * Offset 0x8248 at overlay base 80128158. SHA256(span)=89a1dd448d6b7c2210e7f98888738f4d98ae4401ec24bd0d3bab5b4289a5e2d5.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801303a0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8E0200B4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x30420002)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B8D9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C72A)
MUSASHI_NATIVE_MIPS_WORD(0x24050002)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* HAND MODEL of func_801303A0 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): if s0->unkB4 & 2,
 * func_8012E364(s0) (a0 still holds s0; nop delay slot). Then
 * func_80131CA8(s0, 2) (result ignored). Returns void. */

struct obj_801303A0 {
    u8 pad[0xB4];
    s32 unkB4;
};

extern void func_8012E364(void *arg0);
extern s32 func_80131CA8(void *arg0, s32 arg1);

void func_801303A0(struct obj_801303A0 *arg0) {
    if (arg0->unkB4 & 2) {
        func_8012E364(arg0);
    }
    func_80131CA8(arg0, 2);
}
#endif
