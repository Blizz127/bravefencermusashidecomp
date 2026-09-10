/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015BEE4,8015BF04).
 * Offset 0x33D8C at overlay base 80128158. SHA256(span)=7fe428d51066dfdf13fc5565d79e23157f1e760a16515f57ba0a565ca5c899a9.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015bee4.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C056E54)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015B950();                                  /* static */

void func_8015BEE4(void) {
    func_8015B950();
}
#endif
