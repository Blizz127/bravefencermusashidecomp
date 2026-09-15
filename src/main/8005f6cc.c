/* Exact retail word export for [8005F6CC,8005F704); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x24060010)
MUSASHI_NATIVE_MIPS_WORD(0x3C038008)
MUSASHI_NATIVE_MIPS_WORD(0x24638A48)
MUSASHI_NATIVE_MIPS_WORD(0x10830007)
MUSASHI_NATIVE_MIPS_WORD(0x00C01021)
MUSASHI_NATIVE_MIPS_WORD(0x24C60010)
MUSASHI_NATIVE_MIPS_WORD(0x24A50001)
MUSASHI_NATIVE_MIPS_WORD(0x28A20002)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFFA)
MUSASHI_NATIVE_MIPS_WORD(0x246300F0)
MUSASHI_NATIVE_MIPS_WORD(0x240200FF)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80078A48;

s32 func_8005F6CC(s32 arg0) {
    void *var_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0;

    var_a1 = 0;
    var_a2 = 0x10;
    var_v1 = &D_80078A48;
loop_1:
    var_v0 = var_a2;
    if (arg0 != var_v1) {
        var_a2 += 0x10;
        var_a1 += 1;
        var_v1 += 0xF0;
        if (var_a1 >= 2) {
            var_v0 = 0xFF;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
#endif
