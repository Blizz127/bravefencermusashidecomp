/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174754,80174764).
 * Offset 0x4C5FC at overlay base 80128158. SHA256(span)=19c9a854bc24c7389186d57855f9e3e52ab82f9ebde00228a81aac3dbab48274.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174754.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C4270BC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_801270BC;

s32 func_80174754(void) {
    return D_801270BC;
}
#endif
