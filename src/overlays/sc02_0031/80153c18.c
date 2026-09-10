/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153C18,80153C30).
 * Offset 0x2BAC0 at overlay base 80128158. SHA256(span)=de6f146f1f0b1729d998b8d2a66f6b0395f5b199e4bd95dd168e0cbed4b6db7e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80153c18.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC207518)
MUSASHI_NATIVE_MIPS_WORD(0x3C018011)
MUSASHI_NATIVE_MIPS_WORD(0xAC2051FC)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_801151FC;
extern s32 D_80127518;

void func_80153C18(void) {
    D_80127518 = 0;
    D_801151FC = 0;
}
#endif
