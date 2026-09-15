/* Overlay range [801312D0,80131340) from MAIN.CD member 0012.
 * SHA256(span)=caaf5be818fe92bf35e2de6a45178003f1c34861e867895a2c0195baeab96268.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFB00010)
MUSASHI_NATIVE_MIPS_WORD(0x00A08021)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8C8400BC)
MUSASHI_NATIVE_MIPS_WORD(0x0C04C73D)
MUSASHI_NATIVE_MIPS_WORD(0x2405002E)
MUSASHI_NATIVE_MIPS_WORD(0x10400005)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA6000004)
MUSASHI_NATIVE_MIPS_WORD(0xA6000000)
MUSASHI_NATIVE_MIPS_WORD(0x0804C4CB)
MUSASHI_NATIVE_MIPS_WORD(0xA6020002)
MUSASHI_NATIVE_MIPS_WORD(0x3C058018)
MUSASHI_NATIVE_MIPS_WORD(0x24A5E838)
MUSASHI_NATIVE_MIPS_WORD(0x88A20003)
MUSASHI_NATIVE_MIPS_WORD(0x98A20000)
MUSASHI_NATIVE_MIPS_WORD(0x88A30007)
MUSASHI_NATIVE_MIPS_WORD(0x98A30004)
MUSASHI_NATIVE_MIPS_WORD(0xAA020003)
MUSASHI_NATIVE_MIPS_WORD(0xBA020000)
MUSASHI_NATIVE_MIPS_WORD(0xAA030007)
MUSASHI_NATIVE_MIPS_WORD(0xBA030004)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FB00010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
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

s16 func_80131CF4(s32, s32);                          /* static */

void func_801312D0(void *arg0, void *arg1) {
    s16 temp_v0;

    temp_v0 = func_80131CF4(arg0->unkBC, 0x2E);
    if (temp_v0 != 0) {
        arg1->unk4 = 0;
        arg1->unk0 = 0;
        arg1->unk2 = temp_v0;
        return;
    }
    arg1->unk3 = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
    arg1->unk7 = (unaligned s32) M2C_ERROR(/* Unable to handle lwr; missing a corresponding lwl */);
}
#endif
