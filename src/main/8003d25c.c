/* Exact retail word export for [8003D25C,8003D32C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x04810003)
MUSASHI_NATIVE_MIPS_WORD(0x28820018)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x28820018)
MUSASHI_NATIVE_MIPS_WORD(0x10400008)
MUSASHI_NATIVE_MIPS_WORD(0x28A20018)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24050017)
MUSASHI_NATIVE_MIPS_WORD(0x04A00003)
MUSASHI_NATIVE_MIPS_WORD(0x00A4102A)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00803821)
MUSASHI_NATIVE_MIPS_WORD(0x0800F4C9)
MUSASHI_NATIVE_MIPS_WORD(0x2402FFFD)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x00E5102A)
MUSASHI_NATIVE_MIPS_WORD(0x10400020)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x24080001)
MUSASHI_NATIVE_MIPS_WORD(0x240A0003)
MUSASHI_NATIVE_MIPS_WORD(0x24090002)
MUSASHI_NATIVE_MIPS_WORD(0x00E63021)
MUSASHI_NATIVE_MIPS_WORD(0x00072100)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B54C)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x8C63B0E4)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x00E81004)
MUSASHI_NATIVE_MIPS_WORD(0x00621824)
MUSASHI_NATIVE_MIPS_WORD(0x9482000C)
MUSASHI_NATIVE_MIPS_WORD(0x10600007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0800F4C4)
MUSASHI_NATIVE_MIPS_WORD(0xA0C80000)
MUSASHI_NATIVE_MIPS_WORD(0x0800F4C4)
MUSASHI_NATIVE_MIPS_WORD(0xA0CA0000)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0800F4C4)
MUSASHI_NATIVE_MIPS_WORD(0xA0C90000)
MUSASHI_NATIVE_MIPS_WORD(0xA0C00000)
MUSASHI_NATIVE_MIPS_WORD(0x24E70001)
MUSASHI_NATIVE_MIPS_WORD(0x00E5102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE7)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8006B0E4;
extern s32 D_8006B54C;

s32 func_8003D25C(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a3;
    s32 var_v0;
    s8 *var_a2;
    u16 temp_v0;

    var_a0 = arg0;
    var_a1 = arg1;
    var_v0 = var_a0 < 0x18;
    if (var_a0 < 0) {
        var_a0 = 0;
        var_v0 = 0 < 0x18;
    }
    if (var_v0 != 0) {
        if (var_a1 >= 0x18) {
            var_a1 = 0x17;
        }
        if ((var_a1 < 0) || (var_a3 = var_a0, ((var_a1 < var_a0) != 0))) {
            goto block_7;
        }
        temp_a1 = var_a1 + 1;
        if (var_a3 < temp_a1) {
            var_a2 = var_a3 + arg2;
            do {
                temp_v0 = M2C_FIELD(((var_a3 * 0x10) + D_8006B54C), u16 *, 0xC);
                if (D_8006B0E4 & (1 << var_a3)) {
                    if (temp_v0 != 0) {
                        *var_a2 = 1;
                    } else {
                        *var_a2 = 3;
                    }
                } else if (temp_v0 != 0) {
                    *var_a2 = 2;
                } else {
                    *var_a2 = 0;
                }
                var_a3 += 1;
                var_a2 += 1;
            } while (var_a3 < temp_a1);
        }
        return 0;
    }
block_7:
    return -3;
}
#endif
