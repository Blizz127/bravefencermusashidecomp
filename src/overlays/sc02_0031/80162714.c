/* SC02.CD FILE_031 / ov_SC02_031 retail span [80162714,80162760).
 * Offset 0x3A5BC at overlay base 80128158. SHA256(span)=67bc37ae7aaa3d762088dd3c87b308ba01b44c501162768c6a611e941331c921.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80162714.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A477)
MUSASHI_NATIVE_MIPS_WORD(0x24040012)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x14400009)
MUSASHI_NATIVE_MIPS_WORD(0x2404000C)
MUSASHI_NATIVE_MIPS_WORD(0x0C03435F)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x24040012)
MUSASHI_NATIVE_MIPS_WORD(0x24038000)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A472)
MUSASHI_NATIVE_MIPS_WORD(0x00022C03)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main_0012.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_800291C8(s32, s16);                            /* extern */
s32 func_800291DC();                               /* extern */
s32 func_800D0D7C(s32, s32);                            /* extern */

void func_80162714(void) {
    if ((func_800291DC(0x12) << 0x10) == 0) {
        func_800291C8(0x12, (s16) (func_800D0D7C(0xC, 0) | ~0x7FFF));
    }
}
#endif
