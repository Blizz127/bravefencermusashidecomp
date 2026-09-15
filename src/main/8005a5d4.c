/* Main-exec range [8005A5D4,8005A600) from the SLUS executable.
 * SHA256(span)=6417eaff70c98d24e772b17d889be562dfb583948ad228068c50fe143652f255.
 * Word export for the native seam (m2c produced no draft). */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020002)
MUSASHI_NATIVE_MIPS_WORD(0xA0820003)
MUSASHI_NATIVE_MIPS_WORD(0x10A00002)
MUSASHI_NATIVE_MIPS_WORD(0x3C02E600)
MUSASHI_NATIVE_MIPS_WORD(0x34420002)
MUSASHI_NATIVE_MIPS_WORD(0x10C00002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x34420001)
MUSASHI_NATIVE_MIPS_WORD(0xAC820004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC800008)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8005A5D4(void *arg0, s32 arg1, s32 arg2) {
    s32 var_v0;

    M2C_FIELD(arg0, s8 *, 3) = 2;
    var_v0 = 0xE6000000;
    if (arg1 != 0) {
        var_v0 = 0xE6000002;
    }
    if (arg2 != 0) {
        var_v0 |= 1;
    }
    M2C_FIELD(arg0, s32 *, 4) = var_v0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}
#endif
