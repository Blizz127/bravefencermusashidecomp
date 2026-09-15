/* Exact retail word export for [8004974C,8004978C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x00A01021)
MUSASHI_NATIVE_MIPS_WORD(0x8C890000)
MUSASHI_NATIVE_MIPS_WORD(0x8C8A0004)
MUSASHI_NATIVE_MIPS_WORD(0xACA90004)
MUSASHI_NATIVE_MIPS_WORD(0xACAA0000)
MUSASHI_NATIVE_MIPS_WORD(0xA4A90000)
MUSASHI_NATIVE_MIPS_WORD(0x8C8B0008)
MUSASHI_NATIVE_MIPS_WORD(0x8C89000C)
MUSASHI_NATIVE_MIPS_WORD(0xACAB000C)
MUSASHI_NATIVE_MIPS_WORD(0xACA90008)
MUSASHI_NATIVE_MIPS_WORD(0xA4AA000C)
MUSASHI_NATIVE_MIPS_WORD(0xA4AB0008)
MUSASHI_NATIVE_MIPS_WORD(0x848A0010)
MUSASHI_NATIVE_MIPS_WORD(0xA4A90004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4AA0010)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

void *func_8004974C(void *arg0, void *arg1) {
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t2;
    s32 temp_t3;

    temp_t1 = M2C_FIELD(arg0, s32 *, 0);
    temp_t2 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg1, s32 *, 4) = temp_t1;
    M2C_FIELD(arg1, s32 *, 0) = temp_t2;
    M2C_FIELD(arg1, s32 *, 0) = (s16) temp_t1;
    temp_t3 = M2C_FIELD(arg0, s32 *, 8);
    temp_t1_2 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg1, s32 *, 0xC) = temp_t3;
    M2C_FIELD(arg1, s32 *, 8) = temp_t1_2;
    M2C_FIELD(arg1, s32 *, 0xC) = (s16) temp_t2;
    M2C_FIELD(arg1, s32 *, 8) = (s16) temp_t3;
    M2C_FIELD(arg1, s32 *, 4) = (s16) temp_t1_2;
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) M2C_FIELD(arg0, s16 *, 0x10);
    return arg1;
}
#endif
