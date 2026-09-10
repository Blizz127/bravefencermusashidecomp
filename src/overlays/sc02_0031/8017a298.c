/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017A298,8017A2C0).
 * Offset 0x52140 at overlay base 80128158. SHA256(span)=af2dc0e0f50e1054b30a5afe0ab7817022b7c3ee7903fc1edaa29ecd91a03c9a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017a298.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x2402000E)
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

void func_8017A298(void) {
    s16 sp10;

    sp10 = 0xE;
    func_80179B74(&sp10);
}
#endif
