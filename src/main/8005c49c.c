/* Main-exec range [8005C49C,8005C4CC) from the SLUS executable.
 * SHA256(span)=4ebe3087107934998021d9956d9d646099ebd4ae4a3ddba52286761537cf9b61.
 * Word export for the native seam; the C body below keeps its
 * own oracle match claim. */
#ifdef MUSASHI_NATIVE_MIPS_WORD_EXPORT
MUSASHI_NATIVE_MIPS_WORD(0x3C0341C6)
MUSASHI_NATIVE_MIPS_WORD(0x3C028008)
MUSASHI_NATIVE_MIPS_WORD(0x8C428980)
MUSASHI_NATIVE_MIPS_WORD(0x34634E6D)
MUSASHI_NATIVE_MIPS_WORD(0x00430018)
MUSASHI_NATIVE_MIPS_WORD(0x00002012)
MUSASHI_NATIVE_MIPS_WORD(0x24823039)
MUSASHI_NATIVE_MIPS_WORD(0x3C018008)
MUSASHI_NATIVE_MIPS_WORD(0xAC228980)
MUSASHI_NATIVE_MIPS_WORD(0x00021402)
MUSASHI_NATIVE_MIPS_WORD(0x03E00008)
MUSASHI_NATIVE_MIPS_WORD(0x30427FFF)
#else
#include "psx_types.h"

/* Decompiled by m2c from main.s, then verified byte-exact
 * against retail by tools/match_function.py. Types and signatures are
 * whatever reproduces the bytes; they are not evidence of the
 * original declaration. */

extern u32 D_80078980;

s32 func_8005C49C(void) {
    u32 temp_v0;

    temp_v0 = (D_80078980 * 0x41C64E6D) + 0x3039;
    D_80078980 = temp_v0;
    return (temp_v0 >> 0x10) & 0x7FFF;
}
#endif
