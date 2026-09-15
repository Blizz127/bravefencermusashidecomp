/* Exact retail word export for [8003D3B4,8003D3F8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0x3C028007)
MUSASHI_NATIVE_MIPS_WORD(0x8C42B54C)
MUSASHI_NATIVE_MIPS_WORD(0x00042100)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x00822021)
MUSASHI_NATIVE_MIPS_WORD(0x9482000A)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042FFC0)
MUSASHI_NATIVE_MIPS_WORD(0x00451025)
MUSASHI_NATIVE_MIPS_WORD(0xA482000A)
MUSASHI_NATIVE_MIPS_WORD(0x0C00EC39)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_8006B54C;
void func_8003B0E4(void *);                      /* static */

void func_8003D3B4(s32 arg0, s32 arg1) {
    void *temp_a0;

    temp_a0 = (arg0 * 0x10) + D_8006B54C;
    M2C_FIELD(temp_a0, u16 *, 0xA) = (u16) ((M2C_FIELD(temp_a0, u16 *, 0xA) & 0xFFC0) | arg1);
    func_8003B0E4(temp_a0);
}
#endif
