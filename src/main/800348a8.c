/* Exact retail word export for [800348A8,8003491C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C06800A)
MUSASHI_NATIVE_MIPS_WORD(0x24C646E8)
MUSASHI_NATIVE_MIPS_WORD(0x00001821)
MUSASHI_NATIVE_MIPS_WORD(0x24080005)
MUSASHI_NATIVE_MIPS_WORD(0x3087FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x00042402)
MUSASHI_NATIVE_MIPS_WORD(0x24C50006)
MUSASHI_NATIVE_MIPS_WORD(0x94C20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1448000B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x94A2FFFE)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14470007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x1080000B)
MUSASHI_NATIVE_MIPS_WORD(0x24620001)
MUSASHI_NATIVE_MIPS_WORD(0x94A20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10440007)
MUSASHI_NATIVE_MIPS_WORD(0x24620001)
MUSASHI_NATIVE_MIPS_WORD(0x24630001)
MUSASHI_NATIVE_MIPS_WORD(0x24A50054)
MUSASHI_NATIVE_MIPS_WORD(0x28620008)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFEE)
MUSASHI_NATIVE_MIPS_WORD(0x24C60054)
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

extern u16 D_800A46E8;

s32 func_800348A8(u32 arg0) {
    s32 var_v0;
    s32 var_v1;
    u16 *var_a1;
    u16 *var_a2;
    u32 temp_a0;

    var_a2 = &D_800A46E8;
    var_v1 = 0;
    temp_a0 = arg0 >> 0x10;
    var_a1 = &D_800A46E8 + 6;
loop_1:
    if ((*var_a2 != 5) || (M2C_FIELD(var_a1, u16 *, -2) != (arg0 & 0xFFFF)) || ((var_v0 = var_v1 + 1, (temp_a0 != 0)) && (var_v0 = var_v1 + 1, (M2C_FIELD(var_a1, u16 *, 0) != temp_a0)))) {
        var_v1 += 1;
        var_a1 += 0x54;
        var_a2 += 0x54;
        if (var_v1 >= 8) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
#endif
