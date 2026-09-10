/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153CBC,80153CCC).
 * Offset 0x2BB64 at overlay base 80128158. SHA256(span)=81fb2702933ba00a6a5f0ec4796cc6bf9247f406c4bd78b920e90708de31f3b4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80153cbc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x8C425210)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_80115210;

s32 func_80153CBC(void) {
    return D_80115210;
}
#endif
