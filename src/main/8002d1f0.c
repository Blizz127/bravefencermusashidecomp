/* Native retail instruction export [8002D1F0,8002D240).
 * Verified against asm/main.s and the extracted EXE. No C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800A)
MUSASHI_NATIVE_MIPS_WORD(0x24634ECC)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x00042400)
MUSASHI_NATIVE_MIPS_WORD(0x00042403)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0xAC620000)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xAC244ED0)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA4204ED4)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA4204ED6)
MUSASHI_NATIVE_MIPS_WORD(0x0C00ED17)
MUSASHI_NATIVE_MIPS_WORD(0x00602021)
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

void func_8003B45C(s32 *);                             /* static */
extern s32 D_800A4ECC;
extern s32 D_800A4ED0;
extern s16 D_800A4ED4;
extern s16 D_800A4ED6;

void func_8002D1F0(s16 arg0) {
    D_800A4ECC = 1;
    D_800A4ED0 = (s32) arg0;
    D_800A4ED4 = 0;
    D_800A4ED6 = 0;
    func_8003B45C(&D_800A4ECC);
}
#endif
