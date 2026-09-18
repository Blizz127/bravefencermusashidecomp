/* Exact retail word export for [80014E24,80014E80); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafb00010)
MUSASHI_NATIVE_MIPS_WORD(0x00c08021)
MUSASHI_NATIVE_MIPS_WORD(0x308400ff)
MUSASHI_NATIVE_MIPS_WORD(0x30a500ff)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x14a20005)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x0c005406)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x08005398)
MUSASHI_NATIVE_MIPS_WORD(0x3042ffff)
MUSASHI_NATIVE_MIPS_WORD(0x0c0053b5)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3042ffff)
MUSASHI_NATIVE_MIPS_WORD(0x00501024)
MUSASHI_NATIVE_MIPS_WORD(0x00501026)
MUSASHI_NATIVE_MIPS_WORD(0x2c420001)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0014)
MUSASHI_NATIVE_MIPS_WORD(0x8fb00010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (23/23 words at 0x80014E24). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

s32 func_80014ED4(s32, s32);                        
s32 func_80015018();                        

s32 func_80014E24(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_a1;
    s32 var_v0;

    temp_a0 = arg0 & 0xFF;
    temp_a1 = arg1 & 0xFF;
    if (temp_a1 == 1) {
        var_v0 = func_80015018(temp_a0) & 0xFFFF;
    } else {
        var_v0 = func_80014ED4(temp_a0, temp_a1) & 0xFFFF;
    }
    return (var_v0 & arg2) == arg2;
}
#endif
