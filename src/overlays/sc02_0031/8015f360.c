/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015F360,8015F380).
 * Offset 0x37208 at overlay base 80128158. SHA256(span)=9927974d10a0f01c762e22024d8047e59d734b86a15e545a7d18104bf823dc54.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015f360.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C057CE0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015F380();                                  /* static */

void func_8015F360(void) {
    func_8015F380();
}
#endif
