/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172760,80172780).
 * Offset 0x4A608 at overlay base 80128158. SHA256(span)=7959c3a433d3bf2bec37caa2a838757b04d9684b29bd17feaae0d19c44e026b7.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172760.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D194)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80174650();                                  /* static */

void func_80172760(void) {
    func_80174650();
}
#endif
