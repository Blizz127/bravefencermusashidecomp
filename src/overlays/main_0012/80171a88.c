/* Exact retail word export for [80171A88,80171AB0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x8c820200)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x14400003)
MUSASHI_NATIVE_MIPS_WORD(0x2442ffff)
MUSASHI_NATIVE_MIPS_WORD(0x0805c6aa)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xac820200)
MUSASHI_NATIVE_MIPS_WORD(0x2c420001)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Verified byte-exact against retail by tools/match_function.py
 * (10/10 words at 0x80171A88). Types and signatures are whatever
 * reproduces the bytes; they are not evidence of the original
 * declaration. */
#include "psx_types.h"

s32 func_80171A88(s32 *p) {
    s32 t;

    t = p[128];
    if (t != 0) {
        t -= 1;
        p[128] = t;
        return t == 0;
    }
    return 1;
}
#endif
