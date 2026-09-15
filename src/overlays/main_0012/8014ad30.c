/* Overlay range [8014AD30,8014AD7C) from MAIN.CD member 0012.
 * SHA256(span)=0352d9a38854b257162f8d9d5d95a719be6ffeb2631de3fc64c1efe1284a3bb4.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x94A30000)
MUSASHI_NATIVE_MIPS_WORD(0x94A80002)
MUSASHI_NATIVE_MIPS_WORD(0x94A50004)
MUSASHI_NATIVE_MIPS_WORD(0x2402001D)
MUSASHI_NATIVE_MIPS_WORD(0xAFA40018)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0xAFA6001C)
MUSASHI_NATIVE_MIPS_WORD(0xAFA70020)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30012)
MUSASHI_NATIVE_MIPS_WORD(0xA7A80014)
MUSASHI_NATIVE_MIPS_WORD(0x0C051ABF)
MUSASHI_NATIVE_MIPS_WORD(0xA7A50016)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0030)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_80146AFC(s16 *, u16);                  /* static */

void func_8014AD30(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 sp20;
    s32 sp1C;
    s32 sp18;
    u16 sp16;
    u16 sp14;
    u16 sp12;
    s16 sp10;
    u16 temp_a1;

    temp_a1 = M2C_FIELD(arg1, u16 *, 4);
    sp18 = arg0;
    sp10 = 0x1D;
    sp1C = arg2;
    sp20 = arg3;
    sp12 = M2C_FIELD(arg1, u16 *, 0);
    sp14 = M2C_FIELD(arg1, u16 *, 2);
    sp16 = temp_a1;
    func_80146AFC(&sp10, temp_a1);
}
#endif
