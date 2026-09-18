/* Exact retail word export for [8003819C,800381E4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00052C00)
MUSASHI_NATIVE_MIPS_WORD(0x00052C03)
MUSASHI_NATIVE_MIPS_WORD(0x1CA0000D)
MUSASHI_NATIVE_MIPS_WORD(0x000411C0)
MUSASHI_NATIVE_MIPS_WORD(0x00441023)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x3C03800C)
MUSASHI_NATIVE_MIPS_WORD(0x24639CD8)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x000518C0)
MUSASHI_NATIVE_MIPS_WORD(0x00431821)
MUSASHI_NATIVE_MIPS_WORD(0x24040001)
MUSASHI_NATIVE_MIPS_WORD(0xA4660016)
MUSASHI_NATIVE_MIPS_WORD(0xA4670014)
MUSASHI_NATIVE_MIPS_WORD(0xA0640018)
MUSASHI_NATIVE_MIPS_WORD(0xA04401F4)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern u8 D_800B9CD8[];

void func_8003819C(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    void *temp_v0;
    void *temp_v1;

    if (arg1 <= 0) {
        temp_v0 = &D_800B9CD8[arg0 * 0x1FC];
        temp_v1 = temp_v0 + (arg1 * 8);
        M2C_FIELD(temp_v1, s16 *, 0x16) = arg2;
        M2C_FIELD(temp_v1, s16 *, 0x14) = arg3;
        M2C_FIELD(temp_v1, s8 *, 0x18) = 1;
        M2C_FIELD(temp_v0, s8 *, 0x1F4) = 1;
    }
}
#endif
