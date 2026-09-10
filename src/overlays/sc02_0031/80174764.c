/* SC02.CD FILE_031 / ov_SC02_031 retail span [80174764,80174774).
 * Offset 0x4C60C at overlay base 80128158. SHA256(span)=f7d91d83d490682bf449428cd7e74099a52ee73cd23669d3b71ab216ca889ae8.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80174764.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028012)
MUSASHI_NATIVE_MIPS_WORD(0x8442F9C8)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

extern s16 D_8011F9C8;

s16 func_80174764(void) {
    return D_8011F9C8;
}
#endif
