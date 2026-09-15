/* Exact retail word export for [80054430,800544F8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8c820000)
MUSASHI_NATIVE_MIPS_WORD(0x8c830004)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00402821)
MUSASHI_NATIVE_MIPS_WORD(0x00052823)
MUSASHI_NATIVE_MIPS_WORD(0x04610002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0x00a3102a)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x8c820008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0x00a3102a)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x8c82000c)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0x00a3102a)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x8c820010)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0x00a3102a)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x8c820014)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04410002)
MUSASHI_NATIVE_MIPS_WORD(0x00401821)
MUSASHI_NATIVE_MIPS_WORD(0x00031823)
MUSASHI_NATIVE_MIPS_WORD(0x00a3102a)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00602821)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00a01021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_80054430(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_a1;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    var_v1 = M2C_FIELD(arg0, s32 *, 4);
    var_a1 = temp_v0;
    if (temp_v0 < 0) {
        var_a1 = -var_a1;
    }
    if (var_v1 < 0) {
        var_v1 = -var_v1;
    }
    if (var_a1 < var_v1) {
        var_a1 = var_v1;
    }
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 8);
    var_v1_2 = temp_v0_2;
    if (temp_v0_2 < 0) {
        var_v1_2 = -var_v1_2;
    }
    if (var_a1 < var_v1_2) {
        var_a1 = var_v1_2;
    }
    temp_v0_3 = M2C_FIELD(arg0, s32 *, 0xC);
    var_v1_3 = temp_v0_3;
    if (temp_v0_3 < 0) {
        var_v1_3 = -var_v1_3;
    }
    if (var_a1 < var_v1_3) {
        var_a1 = var_v1_3;
    }
    temp_v0_4 = M2C_FIELD(arg0, s32 *, 0x10);
    var_v1_4 = temp_v0_4;
    if (temp_v0_4 < 0) {
        var_v1_4 = -var_v1_4;
    }
    if (var_a1 < var_v1_4) {
        var_a1 = var_v1_4;
    }
    temp_v0_5 = M2C_FIELD(arg0, s32 *, 0x14);
    var_v1_5 = temp_v0_5;
    if (temp_v0_5 < 0) {
        var_v1_5 = -var_v1_5;
    }
    if (var_a1 < var_v1_5) {
        var_a1 = var_v1_5;
    }
    return var_a1;
}
#endif
