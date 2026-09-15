/* Overlay range [80130088,801300F4) from MAIN.CD member 0012.
 * SHA256(span)=a8c2d8590c6ff08df34ddae94130e50a5368c734aaa46f06406f7ed012930430.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x0C04AF33)
MUSASHI_NATIVE_MIPS_WORD(0x00808021)
MUSASHI_NATIVE_MIPS_WORD(0x34038FFF)
MUSASHI_NATIVE_MIPS_WORD(0x0062182A)
MUSASHI_NATIVE_MIPS_WORD(0x14600007)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x24050032)
MUSASHI_NATIVE_MIPS_WORD(0x1440000A)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x0804C036)
MUSASHI_NATIVE_MIPS_WORD(0x24050033)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x24050033)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x02002021)
MUSASHI_NATIVE_MIPS_WORD(0x24050032)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C6B2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
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

s32 func_8012BCCC();                                /* static */
s32 func_80131AC8(s32, s32);                          /* static */

void func_80130088(s32 arg0) {
    s32 var_a1;
    if (func_8012BCCC() <= 0x8FFF) {
        if (func_80131AC8(arg0, 0x32) == 0) {
            var_a1 = 0x33;
            goto block_5;
        }
    } else if (func_80131AC8(arg0, 0x33) == 0) {
        var_a1 = 0x32;
block_5:
        func_80131AC8(arg0, var_a1);
    }
}
#endif
