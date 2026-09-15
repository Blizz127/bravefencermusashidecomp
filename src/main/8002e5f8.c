/* Exact retail word export for [8002E5F8,8002E638); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20010)
MUSASHI_NATIVE_MIPS_WORD(0xA3A00011)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20012)
MUSASHI_NATIVE_MIPS_WORD(0x0C010E5D)
MUSASHI_NATIVE_MIPS_WORD(0xA3A00013)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA0224F19)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80043974(s8 *);                              /* static */
extern s8 D_800A4F19;

void func_8002E5F8(void) {
    s8 sp13;
    s8 sp12;
    s8 sp11;
    s8 sp10;

    sp10 = 0x80;
    sp11 = 0;
    sp12 = 0x80;
    sp13 = 0;
    func_80043974(&sp10);
    D_800A4F19 = 1;
}
#endif
