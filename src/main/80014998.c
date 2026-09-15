/* Native retail instruction export [80014998,800149E0).
 * Verified against asm/main.s and the extracted EXE. No C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x3C05800B)
MUSASHI_NATIVE_MIPS_WORD(0x24A5F630)
MUSASHI_NATIVE_MIPS_WORD(0x00A01821)
MUSASHI_NATIVE_MIPS_WORD(0x90A20192)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0620051)
MUSASHI_NATIVE_MIPS_WORD(0x90A20193)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xA0620052)
MUSASHI_NATIVE_MIPS_WORD(0x90A20194)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0xA0620053)
MUSASHI_NATIVE_MIPS_WORD(0x28820002)
MUSASHI_NATIVE_MIPS_WORD(0x1440FFF5)
MUSASHI_NATIVE_MIPS_WORD(0x2463005C)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 *D_800AF630;

void func_80014998(void) {
    void *var_v1;
    s32 var_a0;

    var_a0 = 0;
    var_v1 = &D_800AF630;
    do {
        M2C_FIELD(var_v1, u8 *, 0x51) = (u8) M2C_FIELD(&D_800AF630, u8 *, 0x192);
        M2C_FIELD(var_v1, u8 *, 0x52) = (u8) M2C_FIELD(&D_800AF630, u8 *, 0x193);
        var_a0 += 1;
        M2C_FIELD(var_v1, u8 *, 0x53) = (u8) M2C_FIELD(&D_800AF630, u8 *, 0x194);
        var_v1 += 0x5C;
    } while (var_a0 < 2);
}
#endif
