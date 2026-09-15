/* Exact retail word export for [8003B0B8,8003B0E4); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3c048007)
MUSASHI_NATIVE_MIPS_WORD(0x8c84b560)
MUSASHI_NATIVE_MIPS_WORD(0x3c03f0ff)
MUSASHI_NATIVE_MIPS_WORD(0x8c820000)
MUSASHI_NATIVE_MIPS_WORD(0x3463ffff)
MUSASHI_NATIVE_MIPS_WORD(0x00431024)
MUSASHI_NATIVE_MIPS_WORD(0x3c032200)
MUSASHI_NATIVE_MIPS_WORD(0x00431025)
MUSASHI_NATIVE_MIPS_WORD(0xac820000)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (11/11 words at 0x8003B0B8). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

extern volatile s32 *D_8006B560;

void func_8003B0B8(void) {
    *D_8006B560 = (*D_8006B560 & 0xF0FFFFFF) | 0x22000000;
}
#endif
