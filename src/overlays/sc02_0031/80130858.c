/* SC02.CD FILE_031 / ov_SC02_031 retail span [80130858,80130898).
 * Offset 0x8700 at overlay base 80128158. SHA256(span)=804e74fc1c388d32f26216e7a99ec8fe2b915b2f593501025382260479dac56f.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80130858.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AB60)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AFBA)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C678)
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

void func_8012AD80();                                  /* static */
s32 func_8012BEE8(s32);                             /* static */
void func_801319E0(s32);                               /* static */

void func_80130858(s32 arg0) {
    func_8012AD80();
    if (func_8012BEE8(arg0) != 0) {
        func_801319E0(arg0);
    }
}
#endif
