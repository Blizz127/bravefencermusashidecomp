/* Exact retail word export for [8012BEE8,8012BF10); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8c82001c)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2442ffff)
MUSASHI_NATIVE_MIPS_WORD(0x0804afc2)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xac82001c)
MUSASHI_NATIVE_MIPS_WORD(0x2c420001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (10/10 words at 0x8012BEE8). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

s32 func_8012BEE8(s32 *p) {
    s32 t;

    t = p[7];
    if (t != 0) {
        t -= 1;
        p[7] = t;
        return t == 0;
    }
    return 1;
}
#endif
