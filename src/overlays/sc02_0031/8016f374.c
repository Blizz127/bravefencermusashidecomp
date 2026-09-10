/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F374,8016F388).
 * Offset 0x4721C at overlay base 80128158. SHA256(span)=72e04a8d1d49aa938e897dd333ea35228816d2f854127616711edc4621252595.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f374.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0229A17)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s8 D_800B9A17;

void func_8016F374(void) {
    D_800B9A17 = 1;
}
#endif
