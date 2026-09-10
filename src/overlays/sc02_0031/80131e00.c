/* SC02.CD FILE_031 / ov_SC02_031 retail span [80131E00,80131E38).
 * Offset 0x9CA8 at overlay base 80128158. SHA256(span)=1755dbb10099dfdcde344eec19f3bde0ae293a814b209eec844790d6dae95509.
 * Differs from the registry-verified MAIN member 0012 carve in exactly one
 * data reference: D_8017E850 here is D_8017F0D8 (+0x888 member
 * data-block shift). Oracle MATCH re-earned on this file; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xAC8500B0)
MUSASHI_NATIVE_MIPS_WORD(0x00052880)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00250821)
MUSASHI_NATIVE_MIPS_WORD(0x8C22F0D8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0040F809)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
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
typedef void (*CB)();
extern CB D_8017F0D8[];
typedef struct { u8 pad[176]; s32 unk; } T;
void func_80131E00(T *p, s32 idx) {
    p->unk = idx;
    D_8017F0D8[idx](p);
}
#endif
