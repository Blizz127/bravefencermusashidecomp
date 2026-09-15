/* Exact retail word export for [8004787C,800478B8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0x04800005)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c011e2e)
MUSASHI_NATIVE_MIPS_WORD(0x30840fff)
MUSASHI_NATIVE_MIPS_WORD(0x08011e2a)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00042023)
MUSASHI_NATIVE_MIPS_WORD(0x0c011e2e)
MUSASHI_NATIVE_MIPS_WORD(0x30840fff)
MUSASHI_NATIVE_MIPS_WORD(0x00021023)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_800478B8(s32);                             /* static */

s32 func_8004787C(s32 arg0) {
    if (arg0 >= 0) {
        return func_800478B8(arg0 & 0xFFF);
    }
    return -func_800478B8(-arg0 & 0xFFF);
}
#endif
