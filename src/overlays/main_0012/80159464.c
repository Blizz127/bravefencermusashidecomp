/* Overlay range [80159464,801594E8) from MAIN.CD member 0012.
 * SHA256(span)=ac5778006c2faf45085b218661db535c6244eff0d158856fc6fa6f6e246f66a4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0x3C048018)
MUSASHI_NATIVE_MIPS_WORD(0x24840758)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x94830000)
MUSASHI_NATIVE_MIPS_WORD(0x1040000B)
MUSASHI_NATIVE_MIPS_WORD(0x00031400)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800C)
MUSASHI_NATIVE_MIPS_WORD(0x84A59A08)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x10A20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x94830000)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x00031400)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A6A5)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0x14400008)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A6A5)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x14400004)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x08056536)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
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

s32 func_80029A94(s32, s16);                          /* extern */
extern s32 D_80180758;
extern s16 D_800B9A08;

s16 func_80159464(s16 arg1) {
    s32 (*var_a0)();
    s16 var_a1;
    s16 var_v0;
    s32 var_v0_2;

    var_a1 = arg1;
    var_a0 = D_80180758;
    var_v0_2 = (u16) D_80180758 << 0x10;
    if (D_80180758 != 0) {
        var_a1 = D_800B9A08;
loop_2:
        if (var_a1 != (var_v0_2 >> 0x10)) {
            var_a0 += 4;
            var_v0_2 = (u16) *var_a0 << 0x10;
            if (*var_a0 == 0) {
                goto block_4;
            }
            goto loop_2;
        }
        var_v0 = var_a0->unk2;
        /* Duplicate return node #8. Try simplifying control flow for better match */
        return var_v0;
    }
block_4:
    var_v0 = 0;
    if (func_80029A94(1, var_a1) == 0) {
        var_v0 = 0;
        if (func_80029A94(0) == 0) {
            return -1;
        }
    }
    return var_v0;
}
#endif
