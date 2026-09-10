/* SC02.CD FILE_031 / ov_SC02_031 retail span [80152C40,80152C80).
 * Offset 0x2AAE8 at overlay base 80128158. SHA256(span)=a1217cbefb42b4e904a1c4bdc337c8496d1f843ea8e98d81522c13fdddc8c668.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80152c40.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C052408)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C054B20)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0566CF)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C0595C6)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

void func_80149020();                                  /* static */
void func_80152C80(s32);                               /* static */
void func_80159B3C(s32);                               /* static */
void func_80165718(s32);                               /* static */

void func_80152C40(s32 arg0) {
    func_80149020();
    func_80152C80(arg0);
    func_80159B3C(arg0);
    func_80165718(arg0);
}
#endif
