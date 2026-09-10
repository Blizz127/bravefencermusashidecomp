/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017ADE8,8017AE08).
 * Offset 0x52C90 at overlay base 80128158. SHA256(span)=266411a03184626c44d33dd7dc089beec5fd2d5f25a16ec35e4f8948145f0953.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017ade8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05EB43)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8017AD0C();                                  /* static */

void func_8017ADE8(void) {
    func_8017AD0C();
}
#endif
