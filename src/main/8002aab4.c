/* Main-exec range [8002AAB4,8002AB64) from the SLUS executable.
 * SHA256(span)=a1aa49c0b09841e96ad182616376ce8cde4250ad6513e5cb3156c5cd0802f99d.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFB20018)
MUSASHI_NATIVE_MIPS_WORD(0xAFB10014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A89B)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A92E)
MUSASHI_NATIVE_MIPS_WORD(0x00408021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A9CA)
MUSASHI_NATIVE_MIPS_WORD(0x00409021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00AA66)
MUSASHI_NATIVE_MIPS_WORD(0x00408821)
MUSASHI_NATIVE_MIPS_WORD(0x02128021)
MUSASHI_NATIVE_MIPS_WORD(0x02118021)
MUSASHI_NATIVE_MIPS_WORD(0x02021021)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24420003)
MUSASHI_NATIVE_MIPS_WORD(0x3C038006)
MUSASHI_NATIVE_MIPS_WORD(0x246338A0)
MUSASHI_NATIVE_MIPS_WORD(0x8C640000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1080000C)
MUSASHI_NATIVE_MIPS_WORD(0x00028083)
MUSASHI_NATIVE_MIPS_WORD(0x24650004)
MUSASHI_NATIVE_MIPS_WORD(0x0204102A)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x24630008)
MUSASHI_NATIVE_MIPS_WORD(0x8CA20000)
MUSASHI_NATIVE_MIPS_WORD(0x0800AAD2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8C640000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1480FFF7)
MUSASHI_NATIVE_MIPS_WORD(0x24A50008)
MUSASHI_NATIVE_MIPS_WORD(0x3C028006)
MUSASHI_NATIVE_MIPS_WORD(0x8C4238EC)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF001C)
MUSASHI_NATIVE_MIPS_WORD(0x8FB20018)
MUSASHI_NATIVE_MIPS_WORD(0x8FB10014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
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

extern s32 D_800638A0;
extern s32 D_800638EC;
s32 func_8002A26C();                                /* static */
s32 func_8002A4B8();                                /* static */
s32 func_8002A728();                                /* static */
s32 func_8002A998();                                /* static */

s32 func_8002AAB4(void) {
    s32 (*var_v1)();
    s32 *var_a1;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 var_a0;
    s32 var_v0;

    temp_s0 = func_8002A26C();
    temp_s2 = func_8002A4B8();
    temp_s1 = func_8002A728();
    var_v0 = temp_s0 + temp_s2 + temp_s1 + func_8002A998();
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    var_v1 = D_800638A0;
    var_a0 = D_800638A0;
    if (var_a0 != 0) {
        var_a1 = D_800638A0 + 4;
loop_4:
        var_v1 += 8;
        if ((var_v0 >> 2) >= var_a0) {
            return *var_a1;
        }
        var_a0 = *var_v1;
        var_a1 += 8;
        if (var_a0 == 0) {
            goto block_7;
        }
        goto loop_4;
    }
block_7:
    return D_800638EC;
}
#endif
