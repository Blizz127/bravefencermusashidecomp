/* Overlay range [8017DC48,8017DCB0) from MAIN.CD member 0012.
 * SHA256(span)=1c7a8836a1d1776db62d639b25a70f67604568b7602f4c6690850324fd8b6bbd.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00004021)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x28C2000A)
MUSASHI_NATIVE_MIPS_WORD(0x14400012)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x3C096666)
MUSASHI_NATIVE_MIPS_WORD(0x35296667)
MUSASHI_NATIVE_MIPS_WORD(0x00890018)
MUSASHI_NATIVE_MIPS_WORD(0x000417C3)
MUSASHI_NATIVE_MIPS_WORD(0x00005010)
MUSASHI_NATIVE_MIPS_WORD(0x000A1883)
MUSASHI_NATIVE_MIPS_WORD(0x00622023)
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x000418C0)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00C21023)
MUSASHI_NATIVE_MIPS_WORD(0x00E21004)
MUSASHI_NATIVE_MIPS_WORD(0x01024025)
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x28C2000A)
MUSASHI_NATIVE_MIPS_WORD(0x1040FFF2)
MUSASHI_NATIVE_MIPS_WORD(0x24E70004)
MUSASHI_NATIVE_MIPS_WORD(0x00E61004)
MUSASHI_NATIVE_MIPS_WORD(0x01024025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00A81004)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8017DC48(s32 arg0, s32 arg1) {
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_a0 = arg0;
    var_t0 = 0;
    var_a2 = var_a0;
    var_a3 = 0;
    if (var_a2 >= 0xA) {
        do {
            var_a0 /= 0xA;
            var_t0 |= (var_a2 - (var_a0 * 0xA)) << var_a3;
            var_a2 = var_a0;
            var_a3 += 4;
        } while (var_a2 >= 0xA);
    }
    return (var_t0 | (var_a2 << var_a3)) << arg1;
}
#endif
