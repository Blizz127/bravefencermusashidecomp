/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017A360,8017A388).
 * Offset 0x52208 at overlay base 80128158. SHA256(span)=3f9fbcee2cde6dbd6d6faff85592a0f8f785b3f6dfa5c0d3227dbb845cacad72.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017a360.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x2402001E)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C05E6DD)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80179B74(s16 *);                             /* static */

void func_8017A360(void) {
    s16 sp10;

    sp10 = 0x1E;
    func_80179B74(&sp10);
}
#endif
