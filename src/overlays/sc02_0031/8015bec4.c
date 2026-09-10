/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015BEC4,8015BEE4).
 * Offset 0x33D6C at overlay base 80128158. SHA256(span)=7a923dff3f34f9f2c8ba2e0e856d436b9c3e5b5bf8b558a036d68fb387230863.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015bec4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C056B8B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015AE2C();                                  /* static */

void func_8015BEC4(void) {
    func_8015AE2C();
}
#endif
