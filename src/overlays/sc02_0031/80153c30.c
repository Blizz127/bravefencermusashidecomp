/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153C30,80153C44).
 * Offset 0x2BAD8 at overlay base 80128158. SHA256(span)=b3996c84dc96e1973ea5f146e529c95af79ac45f5dda75abe0fe9054f52a5a58.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80153c30.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA422F748)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s16 D_8011F748;

void func_80153C30(void) {
    D_8011F748 = 1;
}
#endif
