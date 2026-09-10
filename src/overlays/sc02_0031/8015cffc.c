/* SC02.CD FILE_031 / ov_SC02_031 retail span [8015CFFC,8015D01C).
 * Offset 0x34EA4 at overlay base 80128158. SHA256(span)=76a665b7626930261dcc3b6b0e69a2ce845c2f92fc0da9c1f53b73eded297324.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8015cffc.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C057407)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8015D01C();                                  /* static */

void func_8015CFFC(void) {
    func_8015D01C();
}
#endif
