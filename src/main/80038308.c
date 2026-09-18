/* Exact retail word export for [80038308,8003834C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x000411C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0x3C04800C)
MUSASHI_NATIVE_MIPS_WORD(0x24849CD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0x00220821)
MUSASHI_NATIVE_MIPS_WORD(0xA0239ED2)
MUSASHI_NATIVE_MIPS_WORD(0x0C00E242)
MUSASHI_NATIVE_MIPS_WORD(0x00442021)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
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

void func_80038908(void *);                            /* static */
extern u8 D_800B9CD8[];
extern u8 D_800B9ED2[];

void func_80038308(s32 arg0) {
    s32 temp_v0;

    temp_v0 = arg0 * 0x1FC;
    D_800B9ED2[temp_v0] = 1;
    func_80038908(&D_800B9CD8[temp_v0]);
}
#endif
