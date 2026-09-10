/* SC02.CD FILE_031 / ov_SC02_031 retail span [801282EC,8012832C).
 * Offset 0x194 at overlay base 80128158. SHA256(span)=b90b21e852a5798e9d24bff374242c4c9d37adb295664a6844aaf392f4084ad6.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/801282ec.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C007032)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0054C4)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04A496)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C04DE3C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C004385)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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

void func_80010E14();                                  /* extern */
void func_80015310();                                  /* extern */
void func_8001C0C8();                                  /* extern */
void func_80129258();                                  /* static */
void func_801378F0();                                  /* static */

void func_801282EC(void) {
    func_8001C0C8();
    func_80015310();
    func_80129258();
    func_801378F0();
    func_80010E14();
}
#endif
