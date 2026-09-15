/* Overlay range [80177784,801777BC) from MAIN.CD member 0012.
 * SHA256(span)=e28f1647fdc59471d42580082d2df201360bf33b7b3a6fdedce5ac1c9e0a6cb5.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0300FF)
MUSASHI_NATIVE_MIPS_WORD(0x3463FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C077480)
MUSASHI_NATIVE_MIPS_WORD(0x34E78080)
MUSASHI_NATIVE_MIPS_WORD(0x2482FFEC)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3C030300)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xAC820000)
MUSASHI_NATIVE_MIPS_WORD(0x24820014)
MUSASHI_NATIVE_MIPS_WORD(0xAC870004)
MUSASHI_NATIVE_MIPS_WORD(0xAC850008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xAC86000C)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void *func_80177784(void *arg0, s32 arg1, s32 arg2) {
    arg0->unk0 = (s32) (((arg0 - 0x14) & 0xFFFFFF) | 0x03000000);
    arg0->unk4 = 0x74808080;
    arg0->unk8 = arg1;
    arg0->unkC = arg2;
    return arg0 + 0x14;
}
#endif
