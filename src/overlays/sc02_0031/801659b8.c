/* SC02.CD FILE_031 / ov_SC02_031 retail span [801659B8,801659CC).
 * Offset 0x3D860 at overlay base 80128158. SHA256(span)=316524b043875f0988d2a8c3053d34ea546def849ec90e6800cd66399168b012.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801659b8.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xAC226B08)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s32 D_80126B08;

void func_801659B8(void) {
    D_80126B08 = 1;
}
#endif
