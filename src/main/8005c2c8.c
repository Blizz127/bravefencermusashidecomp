/* Exact retail word export for [8005C2C8,8005C2F8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x10800009)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0x1ca00003)
MUSASHI_NATIVE_MIPS_WORD(0x00801021)
MUSASHI_NATIVE_MIPS_WORD(0x080170bc)
MUSASHI_NATIVE_MIPS_WORD(0x00001021)
MUSASHI_NATIVE_MIPS_WORD(0xa0800000)
MUSASHI_NATIVE_MIPS_WORD(0x24a5ffff)
MUSASHI_NATIVE_MIPS_WORD(0x1ca0fffd)
MUSASHI_NATIVE_MIPS_WORD(0x24840001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (12/12 words at 0x8005C2C8). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

u8 *func_8005C2C8(u8 *p, s32 n) {
    u8 *start;

    if (p == 0) {
        return 0;
    }
    if (n <= 0) {
        return 0;
    }
    start = p;
    do {
        *p = 0;
        n -= 1;
        p += 1;
    } while (n > 0);
    return start;
}
#endif
