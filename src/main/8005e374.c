/* Exact retail word export for [8005E374,8005E3AC); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x908200e3)
MUSASHI_NATIVE_MIPS_WORD(0x908500e9)
MUSASHI_NATIVE_MIPS_WORD(0x8c8400ec)
MUSASHI_NATIVE_MIPS_WORD(0x24420001)
MUSASHI_NATIVE_MIPS_WORD(0x00021043)
MUSASHI_NATIVE_MIPS_WORD(0x00021080)
MUSASHI_NATIVE_MIPS_WORD(0x00051880)
MUSASHI_NATIVE_MIPS_WORD(0x00651821)
MUSASHI_NATIVE_MIPS_WORD(0x24630003)
MUSASHI_NATIVE_MIPS_WORD(0x30630ffc)
MUSASHI_NATIVE_MIPS_WORD(0x24630004)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00441021)
#else
#include "psx_types.h"
#include "m2c_macros.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

s32 func_8005E374(void *arg0) {
    return (((s32) (M2C_FIELD(arg0, u8 *, 0xE3) + 1) >> 1) * 4) + ((((M2C_FIELD(arg0, u8 *, 0xE9) * 5) + 3) & 0xFFC) + 4) + M2C_FIELD(arg0, s32 *, 0xEC);
}
#endif
