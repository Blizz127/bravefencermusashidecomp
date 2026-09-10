/* Exact retail word export for [80043398,800433C0); EXE-verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27bdffe8)
MUSASHI_NATIVE_MIPS_WORD(0xafbf0010)
MUSASHI_NATIVE_MIPS_WORD(0x3c04f000)
MUSASHI_NATIVE_MIPS_WORD(0x34840003)
MUSASHI_NATIVE_MIPS_WORD(0x0c01739a)
MUSASHI_NATIVE_MIPS_WORD(0x24050020)
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

#include "psx_types.h"

void func_8005CE68(s32, s32);                              /* static */

void func_80043398(void) {
    func_8005CE68(0xF0000003, 0x20);
}
#endif
