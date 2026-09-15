/* Main-exec range [80038A00,80038A58) from the SLUS executable.
 * SHA256(span)=94315ba671b19e37c5ac31e76a55cd302556d6dd80f30f66c106693f1a272e5c.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C058007)
MUSASHI_NATIVE_MIPS_WORD(0x8CA562B0)
MUSASHI_NATIVE_MIPS_WORD(0x3C048007)
MUSASHI_NATIVE_MIPS_WORD(0x248462B4)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x24060002)
MUSASHI_NATIVE_MIPS_WORD(0x90A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14460005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x90820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400007)
MUSASHI_NATIVE_MIPS_WORD(0x00601021)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x28620010)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 *D_800762B0;
extern u8 D_800762B4;

s32 func_80038A00(void) {
    s32 var_v0;
    s32 var_v1;
    u8 *var_a0;
    u8 *var_a1;

    var_a1 = D_800762B0;
    var_a0 = &D_800762B4;
    var_v1 = 0;
loop_1:
    if ((*var_a1 != 2) || (var_v0 = var_v1, (*var_a0 != 0))) {
        var_v1 += 1;
        var_a1 += 1;
        var_a0 += 1;
        if (var_v1 >= 0x10) {
            var_v0 = -1;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
#endif
