/* Exact retail word export for [8002E5BC,8002E5F8); EXE and assembly verified. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x27BDFFE0)
MUSASHI_NATIVE_MIPS_WORD(0x2402005A)
MUSASHI_NATIVE_MIPS_WORD(0x27A40010)
MUSASHI_NATIVE_MIPS_WORD(0xAFBF0018)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20010)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20011)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20012)
MUSASHI_NATIVE_MIPS_WORD(0x0C010E5D)
MUSASHI_NATIVE_MIPS_WORD(0xA3A20013)
MUSASHI_NATIVE_MIPS_WORD(0x3C01800A)
MUSASHI_NATIVE_MIPS_WORD(0xA0204F19)
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

/* Four identical byte stores share one constant load; the last sinks
 * into the call delay slot. m2c's four-scalar form is the same
 * layout; the array states it directly. */
void func_8002E5BC(void) {
    s8 buf[4];

    buf[0] = 0x5A;
    buf[1] = 0x5A;
    buf[2] = 0x5A;
    buf[3] = 0x5A;
    func_80043974(buf);
    D_800A4F19 = 0;
}
#endif
