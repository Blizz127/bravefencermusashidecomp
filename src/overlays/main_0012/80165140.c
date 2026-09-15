/* Overlay range [80165140,801651B8) from MAIN.CD member 0012.
 * SHA256(span)=ea6f85930a93c01b4a4a4dcc2011309efce84bfb89c0bb18359322bf75062d80.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00803821)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x24040008)
MUSASHI_NATIVE_MIPS_WORD(0x3C068018)
MUSASHI_NATIVE_MIPS_WORD(0x24C64398)
MUSASHI_NATIVE_MIPS_WORD(0x8CC2000C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400011)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0xACC4000C)
MUSASHI_NATIVE_MIPS_WORD(0x88E2002F)
MUSASHI_NATIVE_MIPS_WORD(0x98E2002C)
MUSASHI_NATIVE_MIPS_WORD(0x88E30033)
MUSASHI_NATIVE_MIPS_WORD(0x98E30030)
MUSASHI_NATIVE_MIPS_WORD(0xA8C20003)
MUSASHI_NATIVE_MIPS_WORD(0xB8C20000)
MUSASHI_NATIVE_MIPS_WORD(0xA8C30007)
MUSASHI_NATIVE_MIPS_WORD(0xB8C30004)
MUSASHI_NATIVE_MIPS_WORD(0x88E20053)
MUSASHI_NATIVE_MIPS_WORD(0x98E20050)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA8C2000B)
MUSASHI_NATIVE_MIPS_WORD(0xB8C20008)
MUSASHI_NATIVE_MIPS_WORD(0x0805946C)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x28620008)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEA)
MUSASHI_NATIVE_MIPS_WORD(0x24C60010)
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

extern s32 D_80184398;

void func_80165140(void *arg0) {
    s32 (*var_a2)();
    s32 var_v1;

    var_v1 = 0;
    var_a2 = D_80184398;
loop_1:
    var_v1 += 1;
    if (var_a2->unkC == 0) {
        var_a2->unkC = 8;
        var_a2->unk3 = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
        var_a2->unk7 = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
        var_a2->unkB = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
        return;
    }
    var_a2 += 0x10;
    if (var_v1 >= 8) {
        return;
    }
    goto loop_1;
}
#endif
