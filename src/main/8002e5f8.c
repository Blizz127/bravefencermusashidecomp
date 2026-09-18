/* Exact retail word export for [8002E5F8,8002E638); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x24020080)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20010)
MUSASHI_NATIVE_MIPS_WORD(0xA3A00011)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20012)
MUSASHI_NATIVE_MIPS_WORD(0x0C010E5D)
MUSASHI_NATIVE_MIPS_WORD(0xA3A00013)
MUSASHI_NATIVE_MIPS_WORD(0x24020001)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA0224F19)
MUSASHI_NATIVE_MIPS_WORD(0x8FBF0018)
MUSASHI_NATIVE_MIPS_WORD(0x27BD0020)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x00000000)
#else
#include "psx_types.h"

/* Decompiled by hand from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

void func_80043974(s8 *);                              /* static */
extern s8 D_800A4F19;

/* Sibling of func_8002E5BC with a different fill. The buffer must be
 * unsigned: `0x80` overflows `s8` and compiles to `-0x80`, while
 * retail loads `+0x80`. */
void func_8002E5F8(void) {
    u8 buf[4];

    buf[0] = 0x80;
    buf[1] = 0;
    buf[2] = 0x80;
    buf[3] = 0;
    func_80043974(buf);
    D_800A4F19 = 1;
}
#endif
