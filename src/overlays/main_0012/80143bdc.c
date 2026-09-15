/* Overlay range [80143BDC,80143C38) from MAIN.CD member 0012.
 * SHA256(span)=1d2a2196071f42b057de387e5f51d1ca0ad61d74d4afa09598adbb7961ce6b4c.
 * Word export for the native seam; the body below is an
 * UNVERIFIED draft, not an oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFD0)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0028)
MUSASHI_NATIVE_MIPS_WORD(0x94820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20010)
MUSASHI_NATIVE_MIPS_WORD(0x94820002)
MUSASHI_NATIVE_MIPS_WORD(0x00002821)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20012)
MUSASHI_NATIVE_MIPS_WORD(0x94830004)
MUSASHI_NATIVE_MIPS_WORD(0x2402001C)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20016)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xA7A20018)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001A)
MUSASHI_NATIVE_MIPS_WORD(0xAFA00020)
MUSASHI_NATIVE_MIPS_WORD(0xA7A0001E)
MUSASHI_NATIVE_MIPS_WORD(0x0C04B147)
MUSASHI_NATIVE_MIPS_WORD(0xA7A30014)
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

void func_8012C51C(u16 *, s32);              /* static */

void func_80143BDC(void *arg0) {
    s32 sp20;
    s16 sp1E;
    s16 sp1A;
    s16 sp18;
    s16 sp16;
    u16 sp14;
    u16 sp12;
    u16 sp10;

    sp10 = M2C_FIELD(arg0, u16 *, 0);
    sp12 = M2C_FIELD(arg0, u16 *, 2);
    sp16 = 0x1C;
    sp18 = 1;
    sp1A = 0;
    sp20 = 0;
    sp1E = 0;
    sp14 = M2C_FIELD(arg0, u16 *, 4);
    func_8012C51C(&sp10, 0);
}
#endif
