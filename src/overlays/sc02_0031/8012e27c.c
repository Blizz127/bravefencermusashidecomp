/* SC02.CD FILE_031 / ov_SC02_031 retail span [8012E27C,8012E284).
 * Offset 0x6124 at overlay base 80128158. SHA256(span)=5ce5ad86d452c4d2422bd63e15223d5d6b3dfb77f224a88c1f476e9fb34e359d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8012e27c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
#else
#include "psx_types.h"

s32 func_8012E27C(void) {
    return 1;
}
#endif
