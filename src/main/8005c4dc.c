/* Exact retail word export for [8005C4DC,8005C540); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x10800003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14a0000b)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14850003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0801714e)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x1480000e)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x0801714e)
MUSASHI_NATIVE_MIPS_WORD(0x2402ffff)
MUSASHI_NATIVE_MIPS_WORD(0x10c0fff9)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x90860000)
MUSASHI_NATIVE_MIPS_WORD(0x90a30000)
MUSASHI_NATIVE_MIPS_WORD(0x30c200ff)
MUSASHI_NATIVE_MIPS_WORD(0x1043fffa)
MUSASHI_NATIVE_MIPS_WORD(0x24a50001)
MUSASHI_NATIVE_MIPS_WORD(0x90830000)
MUSASHI_NATIVE_MIPS_WORD(0x90a2ffff)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00621023)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8005C4DC(u8 *arg0, u8 *arg1) {
    s32 var_v0;
    u8 *var_a0;
    u8 *var_a1;
    u8 temp_a2;

    var_a0 = arg0;
    var_a1 = arg1;
    if ((var_a0 == 0) || (var_a1 == 0)) {
        if (var_a0 == var_a1) {
            goto block_3;
        }
        var_v0 = 1;
        if (var_a0 == 0) {
            return -1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return var_v0;
    }
loop_7:
    temp_a2 = *var_a0;
    var_a1 += 1;
    if ((temp_a2 & 0xFF) != *var_a1) {
        var_v0 = *var_a0 - M2C_FIELD(var_a1, u8 *, -1);
        return var_v0;
    }
    var_a0 += 1;
    if (temp_a2 != 0) {
        goto loop_7;
    }
block_3:
    return 0;
}
#endif
