/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F1AC,8016F1C4).
 * Offset 0x47054 at overlay base 80128158. SHA256(span)=85fe4aac93380d268bb6e49b342485bafce4c563a481a4b2e433d8db32c78862.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f1ac.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0380FF)
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8C426D50)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
#else
#include "psx_types.h"

extern s32 D_80126D50;

s32 func_8016F1AC(void) {
    return D_80126D50 & 0x80FFFFFF;
}
#endif
