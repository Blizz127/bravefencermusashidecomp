#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x24021000)
MUSASHI_NATIVE_MIPS_WORD(0xA4820000)
MUSASHI_NATIVE_MIPS_WORD(0xA4800002)
MUSASHI_NATIVE_MIPS_WORD(0xA4800004)
MUSASHI_NATIVE_MIPS_WORD(0xA4800006)
MUSASHI_NATIVE_MIPS_WORD(0xA4820008)
MUSASHI_NATIVE_MIPS_WORD(0xA480000A)
MUSASHI_NATIVE_MIPS_WORD(0xA480000C)
MUSASHI_NATIVE_MIPS_WORD(0xA480000E)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA4820010)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_80013F3C(s16 *arg0) {
    arg0[0] = 4096;
    arg0[1] = 0;
    arg0[2] = 0;
    arg0[3] = 0;
    arg0[4] = 4096;
    arg0[5] = 0;
    arg0[6] = 0;
    arg0[7] = 0;
    arg0[8] = 4096;
}
#endif
