/* SC02.CD FILE_031 / ov_SC02_031 retail span [8016F578,8016F5B0).
 * Offset 0x47420 at overlay base 80128158. SHA256(span)=a35f1eb17ddb81ddaf822931224fb1388f7de01c66b8bcae753f160cdd807bc6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/8016f578.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051C21)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C051CAD)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05C64A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80147084();                                  /* static */
void func_801472B4(s32);                               /* static */
void func_80171928(s32);                               /* static */

void func_8016F578(s32 arg0) {
    func_80147084();
    func_801472B4(arg0);
    func_80171928(arg0);
}
#endif
