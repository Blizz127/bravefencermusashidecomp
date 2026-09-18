/* Overlay range [80148038,80148094) from MAIN.CD member 0012.
 * SHA256(span)=1aea098cf9d704ff73f1dc52a1ba23ef1f4bbd392104cd002d8279af4b93dbe1.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830034)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04610008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x04A1000D)
MUSASHI_NATIVE_MIPS_WORD(0x3C02FFE1)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x1440000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08052020)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x18A00006)
MUSASHI_NATIVE_MIPS_WORD(0x3C02001E)
MUSASHI_NATIVE_MIPS_WORD(0x3442FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x0043102A)
MUSASHI_NATIVE_MIPS_WORD(0x10400002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x8C820034)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00451021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC820034)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80148038(void *arg0, s32 arg1) {
    s32 temp_v1;
    s32 var_a1;

    var_a1 = arg1;
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_v1 < 0) {
        if ((var_a1 < 0) && (temp_v1 <= -0x1F0000)) {
            var_a1 = 0;
        }
    } else if ((var_a1 > 0) && (temp_v1 > 0x1EFFFF)) {
        var_a1 = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x34) = (s32) (M2C_FIELD(arg0, s32 *, 0x34) + var_a1);
}
#endif
