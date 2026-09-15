/* Overlay range [8012C51C,8012C588) from MAIN.CD member 0012.
 * SHA256(span)=edde7c6eacd220c84cc5a4f4dbac6f9015f0976aeb1fef6a3499442be260046f.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x3C038012)
MUSASHI_NATIVE_MIPS_WORD(0x24636720)
MUSASHI_NATIVE_MIPS_WORD(0x14C00003)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0804B150)
MUSASHI_NATIVE_MIPS_WORD(0x24659B80)
MUSASHI_NATIVE_MIPS_WORD(0x24C5010C)
MUSASHI_NATIVE_MIPS_WORD(0x10A30008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24A5010C)
MUSASHI_NATIVE_MIPS_WORD(0x14A3FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x10A00003)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B224)
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

s32 func_8012C890(u16 *, s32);                      /* static */
extern s32 *D_80126720;

s32 func_8012C51C(s32 arg1) {
    s32 var_v0;
    u16 *var_a1;

    if (arg1 == 0) {
        var_a1 = &D_80126720 - 0x6480;
    } else {
        var_a1 = arg1 + 0x10C;
    }
    if (var_a1 != &D_80126720) {
loop_4:
        if (*var_a1 != 0) {
            var_a1 += 0x10C;
            if (var_a1 == &D_80126720) {
                goto block_6;
            }
            goto loop_4;
        }
    } else {
block_6:
        var_a1 = 0;
    }
    var_v0 = 0;
    if (var_a1 != 0) {
        var_v0 = func_8012C890(var_a1, arg1);
    }
    return var_v0;
}
#endif
