/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165978,80165988).
 * Offset 0x3D820 at overlay base 80128158. SHA256(span)=eabea0309c98d87c169844648b300071ab5d9ee287405f505c3433b22b3b8cd0.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80165978.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C42672C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_8012672C;

s32 func_80165978(void) {
    return D_8012672C;
}
#endif
