/* Exact retail word export for [8005FBA8,8005FBC8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c021f80)
MUSASHI_NATIVE_MIPS_WORD(0x34421120)
MUSASHI_NATIVE_MIPS_WORD(0x94420000)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800c)
MUSASHI_NATIVE_MIPS_WORD(0xac245320)
MUSASHI_NATIVE_MIPS_WORD(0x3c018008)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xac228f24)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80078F24;
extern s32 D_800C5320;

void func_8005FBA8(s32 arg0) {
    D_800C5320 = arg0;
    D_80078F24 = (s32) *(u16 *)0x1F801120;
}
#endif
