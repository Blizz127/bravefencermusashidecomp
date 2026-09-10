/* SC02.CD FILE_031 / ov_SC02_031 retail span [80160EE0,80160F00).
 * Offset 0x38D88 at overlay base 80128158. SHA256(span)=a152539c0da8afdad90fb4a58421c8475fb47ea32b70dcde559d57fe4ef41c68.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80160ee0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0583C0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80160F00();                                  /* static */

void func_80160EE0(void) {
    func_80160F00();
}
#endif
