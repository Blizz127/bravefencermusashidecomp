/* Exact retail word export for [80018C64,80018CE8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x90820008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x0C0063E2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08006336)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x90820009)
MUSASHI_NATIVE_MIPS_WORD(0x2483002B)
MUSASHI_NATIVE_MIPS_WORD(0xA0820000)
MUSASHI_NATIVE_MIPS_WORD(0x00851021)
MUSASHI_NATIVE_MIPS_WORD(0x9042000A)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x00021027)
MUSASHI_NATIVE_MIPS_WORD(0xA0620000)
MUSASHI_NATIVE_MIPS_WORD(0x28A20002)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x2463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x24050002)
MUSASHI_NATIVE_MIPS_WORD(0x00851021)
MUSASHI_NATIVE_MIPS_WORD(0x9043000A)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0xA043002A)
MUSASHI_NATIVE_MIPS_WORD(0x28A20006)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFB)
MUSASHI_NATIVE_MIPS_WORD(0x00851021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80018F88();                     /* static */

void func_80018C64(void *arg0) {
    s32 var_a1;
    s32 var_a1_2;
    s8 *var_v1;
    u8 temp_v0;
    void *var_v0;

    var_a1 = 0;
    if (M2C_FIELD(arg0, u8 *, 8) != 0) {
        func_80018F88(0);
        return;
    }
    var_v1 = arg0 + 0x2B;
    M2C_FIELD(arg0, u8 *, 0) = (u8) M2C_FIELD(arg0, u8 *, 9);
    do {
        temp_v0 = M2C_FIELD((arg0 + var_a1), u8 *, 0xA);
        var_a1 += 1;
        *var_v1 = ~temp_v0;
        var_v1 -= 1;
    } while (var_a1 < 2);
    var_a1_2 = 2;
    var_v0 = arg0 + 2;
    do {
        var_a1_2 += 1;
        M2C_FIELD(var_v0, u8 *, 0x2A) = (u8) M2C_FIELD(var_v0, u8 *, 0xA);
        var_v0 = arg0 + var_a1_2;
    } while (var_a1_2 < 6);
}
#endif
