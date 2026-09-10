/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F250,8016F264).
 * Offset 0x470F8 at overlay base 80128158. SHA256(span)=e05b0957d80780e28de2d266b0c5d898861f853189062f192f5aa2fd649a73c1.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f250.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA0226D1A)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s8 D_80126D1A;

void func_8016F250(void) {
    D_80126D1A = 1;
}
#endif
