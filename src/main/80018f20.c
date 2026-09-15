/* Exact retail word export for [80018F20,80018F88); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24060002)
MUSASHI_NATIVE_MIPS_WORD(0x24080080)
MUSASHI_NATIVE_MIPS_WORD(0x240700FF)
MUSASHI_NATIVE_MIPS_WORD(0x00862821)
MUSASHI_NATIVE_MIPS_WORD(0x90A30032)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2462FFAF)
MUSASHI_NATIVE_MIPS_WORD(0x2C42005F)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x306300FF)
MUSASHI_NATIVE_MIPS_WORD(0x080063DC)
MUSASHI_NATIVE_MIPS_WORD(0xA0A80032)
MUSASHI_NATIVE_MIPS_WORD(0x2C620008)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x2C6200F8)
MUSASHI_NATIVE_MIPS_WORD(0x080063DC)
MUSASHI_NATIVE_MIPS_WORD(0xA0A00032)
MUSASHI_NATIVE_MIPS_WORD(0x14400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0A70032)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x2CC20008)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFED)
MUSASHI_NATIVE_MIPS_WORD(0x00862821)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80018F20(s32 arg0) {
    u32 temp_v1_2;
    u32 var_a2;
    u8 temp_v1;
    void *var_a1;

    var_a2 = 2;
    var_a1 = arg0 + 2;
    do {
        temp_v1 = M2C_FIELD(var_a1, u8 *, 0x32);
        temp_v1_2 = temp_v1 & 0xFF;
        if ((u32) (temp_v1 - 0x51) < 0x5FU) {
            M2C_FIELD(var_a1, u8 *, 0x32) = 0x80U;
        } else if (temp_v1_2 < 8U) {
            M2C_FIELD(var_a1, u8 *, 0x32) = 0U;
        } else if (temp_v1_2 >= 0xF8U) {
            M2C_FIELD(var_a1, u8 *, 0x32) = 0xFFU;
        }
        var_a2 += 1;
        var_a1 = arg0 + var_a2;
    } while (var_a2 < 8U);
}
#endif
