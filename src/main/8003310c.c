/* Exact retail word export for [8003310C,800331D4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0x3C07800A)
MUSASHI_NATIVE_MIPS_WORD(0x24E746E8)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x24080001)
MUSASHI_NATIVE_MIPS_WORD(0x24E60002)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0xA3A00010)
MUSASHI_NATIVE_MIPS_WORD(0x94E20000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400023)
MUSASHI_NATIVE_MIPS_WORD(0x24A20001)
MUSASHI_NATIVE_MIPS_WORD(0x93A20010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400006)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA3A80010)
MUSASHI_NATIVE_MIPS_WORD(0x94C20000)
MUSASHI_NATIVE_MIPS_WORD(0xAFA50014)
MUSASHI_NATIVE_MIPS_WORD(0x0800CC60)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20018)
MUSASHI_NATIVE_MIPS_WORD(0x94C30000)
MUSASHI_NATIVE_MIPS_WORD(0x97A20018)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0062102B)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30018)
MUSASHI_NATIVE_MIPS_WORD(0xAFA50014)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x24C60054)
MUSASHI_NATIVE_MIPS_WORD(0x28A20008)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFE7)
MUSASHI_NATIVE_MIPS_WORD(0x24E70054)
MUSASHI_NATIVE_MIPS_WORD(0x97A30018)
MUSASHI_NATIVE_MIPS_WORD(0x3082FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0043102B)
MUSASHI_NATIVE_MIPS_WORD(0x14400007)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x97A40014)
MUSASHI_NATIVE_MIPS_WORD(0x0C00CC93)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FA20014)
MUSASHI_NATIVE_MIPS_WORD(0x0800CC71)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
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

void func_8003324C(u16, s32, u16 *, u16 *);            /* static */
extern u16 D_800A46E8;

s32 func_8003310C(s32 arg0) {
    u16 sp18;
    s32 sp14;
    u8 sp10;
    s32 var_a1;
    s32 var_v0;
    u16 *var_a2;
    u16 *var_a3;
    u16 temp_v1;

    var_a3 = &D_800A46E8;
    var_a1 = 0;
    var_a2 = &D_800A46E8 + 2;
    sp10 = 0;
loop_1:
    var_v0 = var_a1 + 1;
    if (*var_a3 != 0) {
        if (sp10 == 0) {
            sp10 = 1;
            sp14 = var_a1;
            sp18 = *var_a2;
        } else {
            temp_v1 = *var_a2;
            if (temp_v1 < sp18) {
                sp18 = temp_v1;
                sp14 = var_a1;
            }
        }
        var_a1 += 1;
        var_a2 += 0x54;
        var_a3 += 0x54;
        if (var_a1 >= 8) {
            if ((u32) (arg0 & 0xFFFF) >= sp18) {
                func_8003324C((u16) sp14, var_a1, var_a2, var_a3);
                return sp14 + 1;
            }
            var_v0 = 0;
            /* Duplicate return node #10. Try simplifying control flow for better match */
            return var_v0;
        }
        goto loop_1;
    }
    return var_v0;
}
#endif
