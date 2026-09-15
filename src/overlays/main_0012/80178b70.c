/* Overlay range [80178B70,80178BB8) from MAIN.CD member 0012.
 * SHA256(span)=6195aca52f7c72ebe8eb395af4e54331577430578e487a3badb4b57cf581f3f8.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x3C108018)
MUSASHI_NATIVE_MIPS_WORD(0x26101CBC)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x0C05E2FE)
MUSASHI_NATIVE_MIPS_WORD(0xAE050000)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x0C05E32F)
MUSASHI_NATIVE_MIPS_WORD(0x2605FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80181CBC;
void func_80178BF8();                                  /* static */
void func_80178CBC(s32, void *);                       /* static */

void func_80178B70(s32 arg0, s32 arg1) {
    D_80181CBC = arg1;
    func_80178BF8();
    func_80178CBC(arg0, D_80181CBC - 0xC);
}
#endif
