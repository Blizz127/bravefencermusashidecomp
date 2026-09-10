/* Exact retail word export for [80014338,80014390); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE8)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A411)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A41B)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A425)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A3F7)
MUSASHI_NATIVE_MIPS_WORD(0x24040007)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A408)
MUSASHI_NATIVE_MIPS_WORD(0x24040007)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A36F)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A380)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0C00A49D)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0010)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0018)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80028DBC();                                 /* static */
void func_80028E00();                                 /* static */
void func_80028FDC();                                 /* static */
void func_80029020();                                 /* static */
void func_80029044();                                  /* static */
void func_8002906C();                                  /* static */
void func_80029094();                                  /* static */
void func_80029274();                                  /* static */

void func_80014338(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80028FDC(7);
    func_80029020(7);
    func_80028DBC(0);
    func_80028E00(0);
    func_80029274();
}
#endif
