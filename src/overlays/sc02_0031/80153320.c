/* SC02.CD FILE_031 / ov_SC02_031 retail span [80153320,8015335C).
 * Offset 0x2B1C8 at overlay base 80128158. SHA256(span)=0fbc159b52b5285a0571c45bd833fda0b578a32b312d1732c1aef7f650c943d7.
 * Differs from the registry-verified MAIN member 0012 carve in one data
 * reference only: the member-0012 table D_80180164 is D_801809EC here
 * (+0x888, the same block shift as the rest of this hole). Oracle MATCH
 * re-earned against the SC02 blob; Not MAIN10.
 */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C018018)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0x8C2209EC)
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
extern CB D_801809EC[];
typedef struct { u8 pad[2]; u16 idx; } T;
void func_80153320(T *p) {
    D_801809EC[p->idx](p);
}
#endif
