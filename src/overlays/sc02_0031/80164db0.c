/* SC02.CD FILE_031 / ov_SC02_031 retail span [80164DB0,80164DD0).
 * Offset 0x3CC58 at overlay base 80128158. SHA256(span)=9e7a20e08351e79b56ce15a8320863009cab18fd7a4704deb4085985cd72a24f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80164db0.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C058B33)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80162CCC();                                  /* static */

void func_80164DB0(void) {
    func_80162CCC();
}
#endif
