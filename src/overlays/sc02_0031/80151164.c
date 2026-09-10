/* SC02.CD FILE_031 / ov_SC02_031 retail span [80151164,80151184).
 * Offset 0x2900C at overlay base 80128158. SHA256(span)=ec7c149ed193f4da71e062c616ccae27b24959be1c969818131b1dcd5409db7a.
 * Re-carve of the registry-verified MAIN member 0012 source
 * src/overlays/main_0012/80151164.c (recovery=c, -O2); the span is
 * byte-identical between member 0012 and SC02_031.
 * Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C054461)
MUSASHI_NATIVE_MIPS_WORD(0x2406000A)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"
void func_80151184();
void func_80151164(void *p, void *q) {
    func_80151184(p, q, 10);
}
#endif
