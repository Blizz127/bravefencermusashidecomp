/* Exact retail word export for [80014928,80014960); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173c2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x3c04801f)
MUSASHI_NATIVE_MIPS_WORD(0x3484f800)
MUSASHI_NATIVE_MIPS_WORD(0x0c017386)
MUSASHI_NATIVE_MIPS_WORD(0x24050800)
MUSASHI_NATIVE_MIPS_WORD(0x0c0173c6)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

#include "psx_types.h"

void func_8005CE18(s32, s32);                              /* static */
void func_8005CF08();                                  /* static */
void func_8005CF18();                                  /* static */

void func_80014928(void) {
    func_8005CF08();
    func_8005CE18(0x801FF800, 0x800);
    func_8005CF18();
}
#endif
