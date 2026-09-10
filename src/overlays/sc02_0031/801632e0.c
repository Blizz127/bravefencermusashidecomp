/* SC02.CD FILE_031 / ov_SC02_031 retail span [801632E0,801632F0).
 * Offset 0x3B188 at overlay base 80128158. SHA256(span)=9e9b3ec187e49c56bfefa145cbe1c92a95b1e8a82b121b7aa78edf5233b94a87.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801632e0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x8C425100)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_80115100;

s32 func_801632E0(void) {
    return D_80115100;
}
#endif
