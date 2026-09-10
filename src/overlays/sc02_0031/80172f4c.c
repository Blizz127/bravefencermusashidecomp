/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172F4C,80172F9C).
 * Offset 0x4ADF4 at overlay base 80128158. SHA256(span)=82f4f7a885bea92fa9e42b56ca1e7a360a38a4f4b89a9c2ff45e4b7cfa3ebad7.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172f4c.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800D)
MUSASHI_NATIVE_MIPS_WORD(0x248447F4)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05CC0F)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x26106B58)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050013)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0xA4206B30)
MUSASHI_NATIVE_MIPS_WORD(0x0C05D194)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80154A74(void *, s32);                            /* static */
void func_8017303C(void *);                               /* static */
void func_80174650(void *);                               /* static */
extern s32 *D_800D47F4;
extern s16 D_80126B30;
extern s32 *D_80126B58;

void func_80172F4C(void) {
    func_8017303C(&D_800D47F4);
    func_80154A74(&D_80126B58, 0x13);
    D_80126B30 = 0;
    func_80174650(&D_80126B58);
}
#endif
