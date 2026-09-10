/* Exact retail word export; no new C match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800b)
MUSASHI_NATIVE_MIPS_WORD(0xa020f7c4)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800b)
MUSASHI_NATIVE_MIPS_WORD(0xa020f7c3)
MUSASHI_NATIVE_MIPS_WORD(0x3c01800b)
MUSASHI_NATIVE_MIPS_WORD(0xa020f7c2)
MUSASHI_NATIVE_MIPS_WORD(0x0c005266)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
MUSASHI_NATIVE_MIPS_WORD(0x8fbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x27bd0018)
MUSASHI_NATIVE_MIPS_WORD(0x03e00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80014998();                                  /* static */
extern s8 D_800AF7C2;
extern s8 D_800AF7C3;
extern s8 D_800AF7C4;

void func_80014960(void) {
    D_800AF7C4 = 0;
    D_800AF7C3 = 0;
    D_800AF7C2 = 0;
    func_80014998();
}
#endif
