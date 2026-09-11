/* Main-exec range [80017E68,80017E8C) from the SLUS executable.
 * SHA256(span)=90acb032f1bd1d3e82722930dd69291ce4b6109cd17178de169b191204b09560.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x84820000)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xACA20014)
MUSASHI_NATIVE_MIPS_WORD(0x84820002)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0xACA20018)
MUSASHI_NATIVE_MIPS_WORD(0x84820004)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xACA2001C)
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

void func_80017E68(s16 *arg0, s32 *arg1) {
    arg1[5] = arg0[0];
    arg1[6] = arg0[1];
    arg1[7] = arg0[2];
}
#endif
