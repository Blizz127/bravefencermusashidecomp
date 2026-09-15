/* Overlay range [80155FF8,80156044) from MAIN.CD member 0012.
 * SHA256(span)=5c14daaabcf08990f47fc15d7c5f8379bb91c4eac1b5d9c88775a0c1ca58ff09.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C021F80)
MUSASHI_NATIVE_MIPS_WORD(0x344203FC)
MUSASHI_NATIVE_MIPS_WORD(0x00404021)
MUSASHI_NATIVE_MIPS_WORD(0x8D090000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xAD3D0000)
MUSASHI_NATIVE_MIPS_WORD(0x2529FFFC)
MUSASHI_NATIVE_MIPS_WORD(0x0120E821)
MUSASHI_NATIVE_MIPS_WORD(0x0C055811)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBD0000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
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

void func_80156044();                                  /* static */

void func_80155FF8(void) {
    **(void ***)0x1F8003FC = sp;
    func_80156044();
}
#endif
