/* Main-exec range [80030470,800304C8) from the SLUS executable.
 * SHA256(span)=cf74af99fc0dc1c651c267e014d5ea880013087db30eecc0cba1b049913bcaf0.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C048003)
MUSASHI_NATIVE_MIPS_WORD(0x248401A4)
MUSASHI_NATIVE_MIPS_WORD(0x0C00DF36)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1040000B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800A)
MUSASHI_NATIVE_MIPS_WORD(0x244246CC)
MUSASHI_NATIVE_MIPS_WORD(0x94430000)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x9084AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x34840002)
MUSASHI_NATIVE_MIPS_WORD(0xA4430000)
MUSASHI_NATIVE_MIPS_WORD(0x3C018007)
MUSASHI_NATIVE_MIPS_WORD(0xA024AEF4)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 func_800301A4;
s32 func_80037CD8(s32 (*)());                         /* static */
extern u8 D_8006AEF4;
extern u16 D_800A46CC;

s32 func_80030470(void) {
    if (func_80037CD8(func_800301A4) != 0) {
        D_800A46CC += 1;
        D_8006AEF4 |= 2;
    }
    return 0;
}
#endif
