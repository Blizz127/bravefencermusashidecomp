/* SC02.CD FILE_031 / ov_SC02_031 retail span [8014A830,8014A850).
 * Offset 0x226D8 at overlay base 80128158. SHA256(span)=fb5497b19d4ca8de36837e61c6250397b704278cb294cf47ed4532bcb46cf513.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8014a830.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C057861)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015E184();                                  /* static */

void func_8014A830(void) {
    func_8015E184();
}
#endif
