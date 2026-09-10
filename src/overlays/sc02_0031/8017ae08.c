/* SC02.CD FILE_031 / ov_SC02_031 retail span [8017AE08,8017AE2C).
 * Offset 0x52CB0 at overlay base 80128158. SHA256(span)=34abac137961b061862613cb08ab76471c5dad673bdd3b30c3e07a16ae9dd7be.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8017ae08.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D1D9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x38420001)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x2C420001)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
#include "psx_types.h"

s32 func_80174764();                                /* static */

s32 func_8017AE08(void) {
    return func_80174764() == 1;
}
#endif
