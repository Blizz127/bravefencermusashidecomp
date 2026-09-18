/* Exact retail word export for [80034B0C,80034B3C); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C03800A)
MUSASHI_NATIVE_MIPS_WORD(0x24634F17)
MUSASHI_NATIVE_MIPS_WORD(0x90650000)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0xA0620000)
MUSASHI_NATIVE_MIPS_WORD(0xA082002A)
MUSASHI_NATIVE_MIPS_WORD(0x240203FF)
MUSASHI_NATIVE_MIPS_WORD(0xA4820026)
MUSASHI_NATIVE_MIPS_WORD(0x24023FFF)
MUSASHI_NATIVE_MIPS_WORD(0xA4820028)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0xA0650000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u8 D_800A4F17;

/* Sibling of func_80034AE0 (only the last store differs): same held
 * flag address, same delay-sunk restore. */
void func_80034B0C(u8 *arg0) {
    u8 *p = &D_800A4F17;
    u8 save = *p;

    *p = 1;
    *(arg0 + 0x2A) = 1;
    *(u16 *)(arg0 + 0x26) = 0x3FF;
    *(u16 *)(arg0 + 0x28) = 0x3FFF;
    *p = save;
}
#endif
