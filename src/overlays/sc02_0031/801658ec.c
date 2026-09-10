/* SC02.CD FILE_031 / ov_SC02_031 retail span [801658EC,80165900).
 * Offset 0x3D794 at overlay base 80128158. SHA256(span)=91e73bac2adbbba74fc6b18f8cbf8aa7cc8757773defcd6194ac85f2d92ed84e.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801658ec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xA0228EC4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s8 D_80078EC4;

void func_801658EC(void) {
    D_80078EC4 = 1;
}
#endif
