/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015BE74,8015BE94).
 * Offset 0x33D1C at overlay base 80128158. SHA256(span)=8853b79c8136dab6b31b4c16f6ddc8ae81feb3a1899abdbb097c7ed20a72dfbb.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015be74.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C056FA5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015BE94();                                  /* static */

void func_8015BE74(void) {
    func_8015BE94();
}
#endif
