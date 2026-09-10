/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153BD8,80153BF0).
 * Offset 0x2BA80 at overlay base 80128158. SHA256(span)=8e5ebd197463e1743b4b2a0bc15c8a7f89afef66308164f3026cce4d1d911ff3.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80153bd8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028011)
MUSASHI_NATIVE_MIPS_WORD(0x8C4251FC)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00821026)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
#else
#include "psx_types.h"

extern s32 D_801151FC;

s32 func_80153BD8(s32 arg0) {
    return arg0 == D_801151FC;
}
#endif
