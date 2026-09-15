/* Overlay range [8012E4C8,8012E504) from MAIN.CD member 0012.
 * SHA256(span)=bb69e77dac1699df5707fbda1a1808fee7122a0db6ca9b5b0d6ad9433ca2b897.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xA462001C)
MUSASHI_NATIVE_MIPS_WORD(0xA4620018)
MUSASHI_NATIVE_MIPS_WORD(0x9482005C)
MUSASHI_NATIVE_MIPS_WORD(0x8C830020)
MUSASHI_NATIVE_MIPS_WORD(0xA4800060)
MUSASHI_NATIVE_MIPS_WORD(0x34420001)
MUSASHI_NATIVE_MIPS_WORD(0xA482005C)
MUSASHI_NATIVE_MIPS_WORD(0x94620012)
MUSASHI_NATIVE_MIPS_WORD(0x24030001)
MUSASHI_NATIVE_MIPS_WORD(0xA483005E)
MUSASHI_NATIVE_MIPS_WORD(0x24420800)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4820062)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main_0012.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void func_8012E4C8(void *arg0) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x20);
    M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_v1, s16 *, 0x18) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0x60) = 0;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 1);
    M2C_FIELD(arg0, s16 *, 0x5E) = 1;
    M2C_FIELD(arg0, s16 *, 0x62) = (s16) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x20), u16 *, 0x12) + 0x800);
}
#endif
