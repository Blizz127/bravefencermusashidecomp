/* SC02.CD FILE_031 / ov_SC02_031 retail span [80155F60,80155F80).
 * Offset 0x2DE08 at overlay base 80128158. SHA256(span)=969f9d5f3a4620be0c4792404967a1d38fead94f844bb5822987d935cd11315b.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80155f60.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C0557E0)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80155F80();                                  /* static */

void func_80155F60(void) {
    func_80155F80();
}
#endif
