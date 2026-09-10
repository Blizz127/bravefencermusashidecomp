/* SC02.CD FILE_031 / ov_SC02_031 retail span [80168A88,80168AA8).
 * Offset 0x40930 at overlay base 80128158. SHA256(span)=c592655b95317df703f4272293b44d921dc5c4a762e32ab99d87c7d9822b36b4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80168a88.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C051B0F)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80146C3C();                                  /* static */

void func_80168A88(void) {
    func_80146C3C();
}
#endif
