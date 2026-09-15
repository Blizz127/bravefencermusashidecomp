/* Overlay range [800CEF94,800CEFF8) from MAIN.CD member 0007.
 * SHA256(span)=b066f19dfab228a0522dba17b459673f258c79750a6decdb0e3628ff9858bf6c.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C02800C)
MUSASHI_NATIVE_MIPS_WORD(0x944299E8)
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800C)
MUSASHI_NATIVE_MIPS_WORD(0xA42299E8)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x00021403)
MUSASHI_NATIVE_MIPS_WORD(0x28420081)
MUSASHI_NATIVE_MIPS_WORD(0x10400006)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00532B)
MUSASHI_NATIVE_MIPS_WORD(0x24050800)
MUSASHI_NATIVE_MIPS_WORD(0x00021400)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C0059EE)
MUSASHI_NATIVE_MIPS_WORD(0x24040004)
MUSASHI_NATIVE_MIPS_WORD(0x0C00462B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0007.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_800118AC();                                  /* extern */
s32 func_80014CAC(s32, s32);                            /* extern */
void func_800167B8();                                 /* extern */
extern u16 D_800B99E8;

void func_800CEF94(void) {
    u16 temp_v0;

    temp_v0 = D_800B99E8 + 1;
    D_800B99E8 = temp_v0;
    if (((s16) temp_v0 >= 0x81) || ((func_80014CAC(0, 0x800) << 0x10) != 0)) {
        func_800167B8(4);
        func_800118AC();
    }
}
#endif
