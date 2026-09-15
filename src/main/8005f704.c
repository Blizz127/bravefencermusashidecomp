/* Exact retail word export for [8005F704,8005F728); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x24428A48)
MUSASHI_NATIVE_MIPS_WORD(0x308400F0)
MUSASHI_NATIVE_MIPS_WORD(0x10800002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x244200F0)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_80078A48;

void *func_8005F704(s32 arg0) {
    void *var_v0;

    var_v0 = &D_80078A48;
    if (arg0 & 0xF0) {
        var_v0 = &D_80078A48 + 0xF0;
    }
    return var_v0;
}
#endif
