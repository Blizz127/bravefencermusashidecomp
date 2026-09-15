/* Exact retail word export [80046BFC,80046C38); verified against pinned EXE and asm. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000A)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00C41021)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800C)
MUSASHI_NATIVE_MIPS_WORD(0x8C637C94)
MUSASHI_NATIVE_MIPS_WORD(0x00021140)
MUSASHI_NATIVE_MIPS_WORD(0x00621821)
MUSASHI_NATIVE_MIPS_WORD(0x00C5102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF8)
MUSASHI_NATIVE_MIPS_WORD(0xAC600000)
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

extern s32 D_800C7C94[];

void func_80046BFC(s32 arg0, u32 arg1) {
    s32 temp_v0;
    u32 var_a2;

    var_a2 = 0;
    if (arg1 != 0) {
        do {
            temp_v0 = var_a2 + arg0;
            var_a2 += 1;
            *(D_800C7C94 + (temp_v0 << 5)) = 0;
        } while (var_a2 < arg1);
    }
}
#endif
