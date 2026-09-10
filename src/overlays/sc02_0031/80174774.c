/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174774,80174784).
 * Offset 0x4C61C at overlay base 80128158. SHA256(span)=bba34870778a8ecf8789b0bd550480ec50af78f074140b597932db85119a59a1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174774.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x84426938)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s16 D_80126938;

s16 func_80174774(void) {
    return D_80126938;
}
#endif
