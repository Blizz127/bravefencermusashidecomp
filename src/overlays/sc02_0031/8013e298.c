/* SC02.CD FILE_031 / ov_SC02_031 retail span [8013E298,8013E2C4).
 * Offset 0x16140 at overlay base 80128158. SHA256(span)=8598f36edc074d30016ddb6ff6f220c96a99441016cb3ae9d007f20d3afd4fc0.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8013e298.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84830004)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x84426CB0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00621023)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021023)
MUSASHI_NATIVE_MIPS_WORD(0x2442FD3F)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x2C42003F)
#else
#include "psx_types.h"

extern s16 D_80126CB0;

/* HAND MODEL of func_8013E298 (main_0012.s), decoded manually from
 * raw asm (fully visible; NOT verified against retail; C89-gated
 * only, promotion requires an oracle MATCH): u32 (s16 *),
 * frameless O2 leaf. Returns |arg0[2] - D_80126CB0| - 0x2C1 < 0x3F
 * (negu absolute value, addiu -0x2C1, sltiu boolean riding the jr
 * delay slot). s16 decl mirrors staging/hand/func_8012BF7C.c. */
u32 func_8013E298(s16 *arg0)
{
    s32 v0;

    v0 = (s32)arg0[2] - (s32)D_80126CB0;
    if (v0 < 0) {
        v0 = -v0;
    }
    v0 -= 0x2C1;
    return (u32)v0 < 0x3F;
}
#endif
