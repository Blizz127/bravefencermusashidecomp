/* SC02.CD FILE_031 / ov_SC02_031 retail span [80172FEC,8017303C).
 * Offset 0x4AE94 at overlay base 80128158. SHA256(span)=0e8b72f99c6c86cb04da0a52a48fe95d17234387c0b9c179735cac555c2ed2c6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80172fec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800D)
MUSASHI_NATIVE_MIPS_WORD(0x24845C6C)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C05CC0F)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108012)
MUSASHI_NATIVE_MIPS_WORD(0x26106B58)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05529D)
MUSASHI_NATIVE_MIPS_WORD(0x24050011)
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
extern s32 *D_800D5C6C;
extern s16 D_80126B30;
extern s32 *D_80126B58;

void func_80172FEC(void) {
    func_8017303C(&D_800D5C6C);
    func_80154A74(&D_80126B58, 0x11);
    D_80126B30 = 0;
    func_80174650(&D_80126B58);
}
#endif
