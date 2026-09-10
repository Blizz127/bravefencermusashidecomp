#include "psx_types.h"

#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a411)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a41b)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a425)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a486)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00640f)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c0063f2)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c006cc9)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a3f7)
MUSASHI_NATIVE_MIPS_WORD(0x24040007)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a408)
MUSASHI_NATIVE_MIPS_WORD(0x24040007)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a36f)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x0c00a380)
MUSASHI_NATIVE_MIPS_WORD(0x00002021)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#endif

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80018FC8();                                  /* static */
void func_8001903C();                                  /* static */
void func_8001B324();                                  /* static */
void func_80028DBC();                                 /* static */
void func_80028E00();                                 /* static */
void func_80028FDC();                                 /* static */
void func_80029020();                                 /* static */
void func_80029044();                                  /* static */
void func_8002906C();                                  /* static */
void func_80029094();                                  /* static */
void func_80029218();                                  /* static */

void func_800142C8(void) {
    func_80029044();
    func_8002906C();
    func_80029094();
    func_80029218();
    func_8001903C();
    func_80018FC8();
    func_8001B324();
    func_80028FDC(7);
    func_80029020(7);
    func_80028DBC(0);
    func_80028E00(0);
}
