/* SC02.CD FILE_031 / ov_SC02_031 retail span [80165900,80165910).
 * Offset 0x3D7A8 at overlay base 80128158. SHA256(span)=9c6cebe1deb420277c96a1605a170ea2ffdbb2245e1631d24348f00fb4c5bb64.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80165900.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x90428EC4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern u8 D_80078EC4;

u8 func_80165900(void) {
    return D_80078EC4;
}
#endif
