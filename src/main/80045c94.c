/* Exact retail word export for [80045C94,80045D00); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffd8)
MUSASHI_NATIVE_MIPS_WORD(0xafb1001c)
MUSASHI_NATIVE_MIPS_WORD(0x00808821)
MUSASHI_NATIVE_MIPS_WORD(0x00a02021)
MUSASHI_NATIVE_MIPS_WORD(0x27a50010)
MUSASHI_NATIVE_MIPS_WORD(0xafb00018)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0020)
MUSASHI_NATIVE_MIPS_WORD(0x0c010e86)
MUSASHI_NATIVE_MIPS_WORD(0x00c08021)
MUSASHI_NATIVE_MIPS_WORD(0x24040002)
MUSASHI_NATIVE_MIPS_WORD(0x27a50010)
MUSASHI_NATIVE_MIPS_WORD(0x0c010d73)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x02202021)
MUSASHI_NATIVE_MIPS_WORD(0x02002821)
MUSASHI_NATIVE_MIPS_WORD(0x0c0118df)
MUSASHI_NATIVE_MIPS_WORD(0x24060080)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c011920)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0x2c420001)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0020)
MUSASHI_NATIVE_MIPS_WORD(0x8fb1001c)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00018)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0028)
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

void func_800435CC(s32, void *, s32);                         /* static */
void func_80043A18(s32, void *);                            /* static */
void func_8004637C(s32, s32, s32);                         /* static */
s32 func_80046480(s32, s32);                            /* static */

s32 func_80045C94(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    func_80043A18(arg1, &sp10);
    func_800435CC(2, &sp10, 0);
    func_8004637C(arg0, arg2, 0x80);
    return func_80046480(0, 0) == 0;
}
#endif
