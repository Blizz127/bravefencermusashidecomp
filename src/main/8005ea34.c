/* Exact retail word export for [8005EA34,8005EA54); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24020043)
MUSASHI_NATIVE_MIPS_WORD(0xa0820036)
MUSASHI_NATIVE_MIPS_WORD(0x24820024)
MUSASHI_NATIVE_MIPS_WORD(0xac82002c)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xa0850024)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0xa0820035)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (8/8 words at 0x8005EA34). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

void func_8005EA34(u8 *p, s32 arg) {
    p[0x36] = 0x43;
    *(u8 **) (p + 0x2C) = p + 0x24;
    p[0x24] = arg;
    p[0x35] = 1;
}
#endif
