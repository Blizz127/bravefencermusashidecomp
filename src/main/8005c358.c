/* Exact retail word export for [8005C358,8005C388); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x10800009)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x1cc00003)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x080170e0)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0xa0850000)
MUSASHI_NATIVE_MIPS_WORD(0x24c6ffff)
MUSASHI_NATIVE_MIPS_WORD(0x1cc0fffd)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (12/12 words at 0x8005C358). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

u8 *func_8005C358(u8 *p, s32 value, s32 n) {
    u8 *start;

    if (p == 0) {
        return 0;
    }
    if (n <= 0) {
        return 0;
    }
    start = p;
    do {
        *p = (u8) value;
        n -= 1;
        p += 1;
    } while (n > 0);
    return start;
}
#endif
