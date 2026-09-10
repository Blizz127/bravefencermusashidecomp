/* SC02.CD FILE_031 / ov_SC02_031 retail span [80170C44,80170C74).
 * Offset 0x48AEC at overlay base 80128158. SHA256(span)=5877c0599ca48badfc74ed2f3c96b37b5f2d4ee98debaa7c15e7ec5ec212e2ff.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80170c44.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C18)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80147060();                                  /* static */
void func_80171928(s32);                               /* static */

void func_80170C44(s32 arg0) {
    func_80147060();
    func_80171928(arg0);
}
#endif
