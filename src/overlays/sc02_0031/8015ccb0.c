/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015CCB0,8015CCD0).
 * Offset 0x34B58 at overlay base 80128158. SHA256(span)=2275cbf24a77ff4b596d1216ee8b2998abd1797e3491c8679f4020430211e95e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015ccb0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C057334)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015CCD0();                                  /* static */

void func_8015CCB0(void) {
    func_8015CCD0();
}
#endif
