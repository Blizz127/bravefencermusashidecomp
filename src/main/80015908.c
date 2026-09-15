/* Exact retail word export for [80015908,80015954); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x30A50080)
MUSASHI_NATIVE_MIPS_WORD(0x10A00005)
MUSASHI_NATIVE_MIPS_WORD(0x308200FF)
MUSASHI_NATIVE_MIPS_WORD(0x14A00009)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFE0)
MUSASHI_NATIVE_MIPS_WORD(0x08005653)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x2442FFE0)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x3C038006)
MUSASHI_NATIVE_MIPS_WORD(0x24632A78)
MUSASHI_NATIVE_MIPS_WORD(0x08005653)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x00021040)
MUSASHI_NATIVE_MIPS_WORD(0x3C038006)
MUSASHI_NATIVE_MIPS_WORD(0x24632AF8)
MUSASHI_NATIVE_MIPS_WORD(0x00431021)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Body below is an UNVERIFIED draft, not an oracle match
 * claim; promotion requires tools/match_function.py MATCH. */
#include "psx_types.h"

/* m2c draft from main.s: NOT verified against retail. C89-gated only;
 * promotion requires an oracle MATCH (tools/match_function.py). Types
 * and signatures are whatever the decompiler guessed; they are not
 * evidence of the original declaration. */

extern s32 D_80062A78;
extern s32 D_80062AF8;

s32 func_80015908(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_a1 = arg1 & 0x80;
    temp_v0 = arg0 & 0xFF;
    if (temp_a1 != 0) {
        temp_v0_2 = temp_v0 - 0x20;
        if (temp_a1 == 0) {
            return temp_v0_2;
        }
        return (s32) ((temp_v0_2 * 2) + D_80062AF8);
    }
    return (s32) (((temp_v0 - 0x20) * 2) + D_80062A78);
}
#endif
