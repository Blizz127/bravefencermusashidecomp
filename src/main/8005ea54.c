/* Exact retail word export for [8005EA54,8005EA68); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020045)
MUSASHI_NATIVE_MIPS_WORD(0xa0820036)
MUSASHI_NATIVE_MIPS_WORD(0xac80002c)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xa0800035)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (5/5 words at 0x8005EA54). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

void func_8005EA54(u8 *p) {
    p[0x36] = 0x45;
    *(s32 *) (p + 0x2C) = 0;
    p[0x35] = 0;
}
#endif
