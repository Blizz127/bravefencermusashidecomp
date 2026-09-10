/* SC02.CD FILE_031 / ov_SC02_031 retail span [801749A8,801749C8).
 * Offset 0x4C850 at overlay base 80128158. SHA256(span)=1013f37e86f0d2ed8316d17a4fa663c03c9e3af9945c888f438ae4982379160d.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801749a8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D272)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_801749C8();                                  /* static */

void func_801749A8(void) {
    func_801749C8();
}
#endif
