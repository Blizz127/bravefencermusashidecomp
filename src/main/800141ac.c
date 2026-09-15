/* Main-exec range [800141AC,800141F0) from the SLUS executable.
 * SHA256(span)=88c68ea15e7e114370141d22e28d89a0d20b00d42b69e79f0dc95c6e318b88b7.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x00A03021)
MUSASHI_NATIVE_MIPS_WORD(0x8CC20000)
MUSASHI_NATIVE_MIPS_WORD(0x8CC30004)
MUSASHI_NATIVE_MIPS_WORD(0x8CC50008)
MUSASHI_NATIVE_MIPS_WORD(0x8CC7000C)
MUSASHI_NATIVE_MIPS_WORD(0xAFA20010)
MUSASHI_NATIVE_MIPS_WORD(0xAFA30014)
MUSASHI_NATIVE_MIPS_WORD(0xAFA50018)
MUSASHI_NATIVE_MIPS_WORD(0xAFA7001C)
MUSASHI_NATIVE_MIPS_WORD(0x0C01213B)
MUSASHI_NATIVE_MIPS_WORD(0x27A50010)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0020)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_800484EC(s32 *, void *, s32);          /* static */

void func_800141AC(void *arg1) {
    s32 sp1C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 temp_a3;

    temp_a3 = M2C_FIELD(arg1, s32 *, 0xC);
    sp10 = M2C_FIELD(arg1, s32 *, 0);
    sp14 = M2C_FIELD(arg1, s32 *, 4);
    sp18 = M2C_FIELD(arg1, s32 *, 8);
    sp1C = temp_a3;
    func_800484EC(&sp10, arg1, temp_a3);
}
#endif
