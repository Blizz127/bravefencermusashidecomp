/* Exact retail word export for [80010D60,80010DA0); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0014)
MUSASHI_NATIVE_MIPS_WORD(0xAFBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x03A0F021)
MUSASHI_NATIVE_MIPS_WORD(0x240403E0)
MUSASHI_NATIVE_MIPS_WORD(0x0C0042B8)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x24040005)
MUSASHI_NATIVE_MIPS_WORD(0x0C004606)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x03C0E821)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0014)
MUSASHI_NATIVE_MIPS_WORD(0x8FBE0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80010AE0();                                 /* static */
void func_80011818();                                 /* static */

void func_80010D60(void) {
    func_80010AE0(0x3E0);
    func_80011818(5);
}
#endif
