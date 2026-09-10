/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F388,8016F398).
 * Offset 0x47230 at overlay base 80128158. SHA256(span)=3427fcdb03f49a46befe4330ea6616c1cec0a92145716e6f3b8e431731c864ab.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f388.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA0209A17)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s8 D_800B9A17;

void func_8016F388(void) {
    D_800B9A17 = 0;
}
#endif
