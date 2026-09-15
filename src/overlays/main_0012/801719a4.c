/* Overlay range [801719A4,80171A04) from MAIN.CD member 0012.
 * SHA256(span)=1e4261792af44e9d627aa8a2e58189312129372bb0bc8f28d2da50eee4326344.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFF8)
MUSASHI_NATIVE_MIPS_WORD(0x10A0000F)
MUSASHI_NATIVE_MIPS_WORD(0x00003021)
MUSASHI_NATIVE_MIPS_WORD(0x00003821)
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0x8C8301FC)
MUSASHI_NATIVE_MIPS_WORD(0x00461021)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x8C420000)
MUSASHI_NATIVE_MIPS_WORD(0x24C60001)
MUSASHI_NATIVE_MIPS_WORD(0x3C018012)
MUSASHI_NATIVE_MIPS_WORD(0x00270821)
MUSASHI_NATIVE_MIPS_WORD(0xAC22F738)
MUSASHI_NATIVE_MIPS_WORD(0x00C5102B)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF4)
MUSASHI_NATIVE_MIPS_WORD(0x24E70004)
MUSASHI_NATIVE_MIPS_WORD(0x90820214)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00461021)
MUSASHI_NATIVE_MIPS_WORD(0xA0820214)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0008)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_8011F738;

void func_801719A4(void *arg0, u32 arg1) {
    s32 temp_v0;
    s32 var_a3;
    u32 var_a2;

    var_a2 = 0;
    if (arg1 != 0) {
        var_a3 = 0;
        do {
            temp_v0 = *(((arg0->unk214 + var_a2) * 4) + arg0->unk1FC);
            var_a2 += 1;
            *(&D_8011F738 + var_a3) = temp_v0;
            var_a3 += 4;
        } while (var_a2 < arg1);
    }
    arg0->unk214 = (u8) (arg0->unk214 + var_a2);
}
#endif
