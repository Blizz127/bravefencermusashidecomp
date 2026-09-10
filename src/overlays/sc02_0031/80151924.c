/* SC02.CD FILE_031 / ov_SC02_031 retail span [80151924,80151944).
 * Offset 0x297CC at overlay base 80128158. SHA256(span)=164661efd047780662814915f3209c8b4ebe74528662878035bbcfd2dc3c4663.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80151924.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C054651)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80151944();                                  /* static */

void func_80151924(void) {
    func_80151944();
}
#endif
