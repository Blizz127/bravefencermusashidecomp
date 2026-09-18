/* Exact retail word export for [80029A58,80029A94); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00041040)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
MUSASHI_NATIVE_MIPS_WORD(0x000210c0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x000210c0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3c038008)
MUSASHI_NATIVE_MIPS_WORD(0x24638f28)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x8c430038)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x00031842)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xac430038)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (15/15 words at 0x80029A58). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"
#include "m2c_macros.h"

extern u8 D_80078F28[];

void func_80029A58(s32 arg0) {
    void *temp_v0;

    temp_v0 = &D_80078F28[arg0 * 0x2DC];
    M2C_FIELD(temp_v0, u32 *, 0x38) = (u32) ((u32) M2C_FIELD(temp_v0, u32 *, 0x38) >> 1);
}
#endif
