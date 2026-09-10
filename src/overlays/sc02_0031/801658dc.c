/* SC02.CD FILE_031 / ov_SC02_031 retail span [801658DC,801658EC).
 * Offset 0x3D784 at overlay base 80128158. SHA256(span)=6701d601e14267214dfe5ceb22343e23d5c532ad1a937bc8a4a4836ef176ed2b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801658dc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xA0208EC4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s8 D_80078EC4;

void func_801658DC(void) {
    D_80078EC4 = 0;
}
#endif
