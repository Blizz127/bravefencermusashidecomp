/* SC02.CD FILE_031 / ov_SC02_031 retail span [80157880,801578C0).
 * Offset 0x2F728 at overlay base 80128158. SHA256(span)=2bf1cd8e90bc64dc4b71a77bad32c33a843786cab07b279ebfad4d3ca881fdf4.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80157880.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C053B4A)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0534F8)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C053E81)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C055E30)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_8014D3E0(s32);                               /* static */
void func_8014ED28();                                  /* static */
void func_8014FA04(s32);                               /* static */
void func_801578C0(s32);                               /* static */

void func_80157880(s32 arg0) {
    func_8014ED28();
    func_8014D3E0(arg0);
    func_8014FA04(arg0);
    func_801578C0(arg0);
}
#endif
