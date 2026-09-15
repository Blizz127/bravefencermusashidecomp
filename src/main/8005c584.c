/* Exact retail word export for [8005C584,8005C604); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x10800003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14a00007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10850018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14800017)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0801717f)
MUSASHI_NATIVE_MIPS_WORD(0x2402ffff)
MUSASHI_NATIVE_MIPS_WORD(0x24c6ffff)
MUSASHI_NATIVE_MIPS_WORD(0x04c00012)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x90830000)
MUSASHI_NATIVE_MIPS_WORD(0x90a20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14620006)
MUSASHI_NATIVE_MIPS_WORD(0x24a50001)
MUSASHI_NATIVE_MIPS_WORD(0x1060000a)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x24c6ffff)
MUSASHI_NATIVE_MIPS_WORD(0x04c1fff7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04c00005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x90830000)
MUSASHI_NATIVE_MIPS_WORD(0x90a2ffff)
MUSASHI_NATIVE_MIPS_WORD(0x0801717f)
MUSASHI_NATIVE_MIPS_WORD(0x00621023)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8005C584(u8 *arg0, u8 *arg1, s32 arg2) {
    s32 var_a2;
    s32 var_v0;
    u8 *var_a0;
    u8 *var_a1;
    u8 temp_v1;

    var_a0 = arg0;
    var_a1 = arg1;
    if ((var_a0 == 0) || (var_a1 == 0)) {
        if (var_a0 != var_a1) {
            var_v0 = 1;
            if (var_a0 == 0) {
                return -1;
            }
            /* Duplicate return node #12. Try simplifying control flow for better match */
            return var_v0;
        }
        goto block_11;
    }
    var_a2 = arg2 - 1;
    var_v0 = 0;
    if (var_a2 >= 0) {
loop_6:
        temp_v1 = *var_a0;
        var_a1 += 1;
        if (temp_v1 == *var_a1) {
            var_a0 += 1;
            if (temp_v1 != 0) {
                var_a2 -= 1;
                if (var_a2 < 0) {
                    goto block_9;
                }
                goto loop_6;
            }
            goto block_11;
        }
block_9:
        if (var_a2 >= 0) {
            return *var_a0 - M2C_FIELD(var_a1, u8 *, -1);
        }
block_11:
        var_v0 = 0;
        /* Duplicate return node #12. Try simplifying control flow for better match */
        return var_v0;
    }
    return var_v0;
}
#endif
