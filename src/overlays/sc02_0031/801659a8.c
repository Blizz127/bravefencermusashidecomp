/* SC02.CD FILE_031 / ov_SC02_031 retail span [801659A8,801659B8).
 * Offset 0x3D850 at overlay base 80128158. SHA256(span)=8dc7bb115ec255ce3f623e1c5eaa6d49349ea2aa2493efa15362f006b7d7e942.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801659a8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028013)
MUSASHI_NATIVE_MIPS_WORD(0x8C42811C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_8012811C;

s32 func_801659A8(void) {
    return D_8012811C;
}
#endif
