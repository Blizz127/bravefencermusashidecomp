/* Main-exec range [80018384,800183E0) from the SLUS executable.
 * SHA256(span)=8ea31fbd6b652e3f89806eab129ab02cdc782e93690058f7ae7c74a2055c31b7.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00803021)
MUSASHI_NATIVE_MIPS_WORD(0x3C02800B)
MUSASHI_NATIVE_MIPS_WORD(0x2442E610)
MUSASHI_NATIVE_MIPS_WORD(0x0046102B)
MUSASHI_NATIVE_MIPS_WORD(0x10400003)
MUSASHI_NATIVE_MIPS_WORD(0x00A03821)
MUSASHI_NATIVE_MIPS_WORD(0x080060E7)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3C0400FF)
MUSASHI_NATIVE_MIPS_WORD(0x3484FFFF)
MUSASHI_NATIVE_MIPS_WORD(0x3C05FF00)
MUSASHI_NATIVE_MIPS_WORD(0x8CE30000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x00651824)
MUSASHI_NATIVE_MIPS_WORD(0x00441024)
MUSASHI_NATIVE_MIPS_WORD(0x00621825)
MUSASHI_NATIVE_MIPS_WORD(0xACE30000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x00E42024)
MUSASHI_NATIVE_MIPS_WORD(0x00451024)
MUSASHI_NATIVE_MIPS_WORD(0x00441025)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACC20000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_800AE610;

void func_80018384(u32 arg0, s32 *arg1) {
    if ((u32) &D_800AE610 < arg0) {
loop_1:
        goto loop_1;
    }
    *arg1 = (*arg1 & 0xFF000000) | (*arg0 & 0xFFFFFF);
    *arg0 = (s32) ((*arg0 & 0xFF000000) | ((s32) arg1 & 0xFFFFFF));
}
#endif
