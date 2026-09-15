/* Main-exec range [80058F44,80058F70) from the SLUS executable.
 * SHA256(span)=22889462dff9f64b9d44aeb687752f3932c9ea6966836adce80d2237e6c891bc.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x10C00002)
MUSASHI_NATIVE_MIPS_WORD(0x3C03E100)
MUSASHI_NATIVE_MIPS_WORD(0x34630200)
MUSASHI_NATIVE_MIPS_WORD(0x10A00002)
MUSASHI_NATIVE_MIPS_WORD(0x30E209FF)
MUSASHI_NATIVE_MIPS_WORD(0x34420400)
MUSASHI_NATIVE_MIPS_WORD(0x00621025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80058F44(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_v0;
    s32 var_v1;

    M2C_FIELD(arg0, s8 *, 3) = 1;
    var_v1 = 0xE1000000;
    if (arg2 != 0) {
        var_v1 = 0xE1000200;
    }
    var_v0 = arg3 & 0x9FF;
    if (arg1 != 0) {
        var_v0 |= 0x400;
    }
    M2C_FIELD(arg0, s32 *, 4) = (s32) (var_v1 | var_v0);
}
#endif
