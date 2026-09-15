/* Main-exec range [8005B6C0,8005B710) from the SLUS executable.
 * SHA256(span)=659c212d27bb10812c58508c78c09460c1d5f9799e7cf80eb60d3af7e1859e99.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x24A6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C038007)
MUSASHI_NATIVE_MIPS_WORD(0x8C63285C)
MUSASHI_NATIVE_MIPS_WORD(0x3C020400)
MUSASHI_NATIVE_MIPS_WORD(0xAC620000)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x2405FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x8C830000)
MUSASHI_NATIVE_MIPS_WORD(0x24840004)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C422858)
MUSASHI_NATIVE_MIPS_WORD(0x24C6FFFF)
MUSASHI_NATIVE_MIPS_WORD(0xAC430000)
MUSASHI_NATIVE_MIPS_WORD(0x14C5FFF9)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80072858;
extern s32 *D_8007285C;

s32 func_8005B6C0(s32 *arg0, s32 arg1) {
    s32 *var_a0;
    s32 temp_v1;
    s32 var_a2;

    var_a0 = arg0;
    var_a2 = arg1 - 1;
    *D_8007285C = 0x04000000;
    if (arg1 != 0) {
        do {
            temp_v1 = *var_a0;
            var_a0 += 4;
            var_a2 -= 1;
            *D_80072858 = temp_v1;
        } while (var_a2 != -1);
    }
    return 0;
}
#endif
